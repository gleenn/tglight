// Controls TCL controller.

#include <stdio.h>

#define uint8_t  unsigned char

#define STRAND_COUNT    8
#define STRAND_LENGTH   512

struct Strands {
  Strands() {
    for (int i = 0; i < STRAND_COUNT; i++) {
      colors[i] = new uint8_t[STRAND_LENGTH * 3];
      lengths[i] = 0;
    }
  }

  ~Strands() {
    for (int i = 0; i < STRAND_COUNT; i++) {
      delete[] colors[i];
    }
  }

  uint8_t* colors[STRAND_COUNT];
  int lengths[STRAND_COUNT];

private:
  Strands(const Strands& src);
};

struct Layout {
  Layout() {
    memset(lengths, 0, sizeof(lengths));
  }

  int x[STRAND_COUNT][STRAND_LENGTH];
  int y[STRAND_COUNT][STRAND_LENGTH];
  int lengths[STRAND_COUNT];
};

// To use this class:
//   renderer = TclRenderer(controller_id)
//   renderer.set_layout('layout.dxf', width, height)
//   // 'image_colors' has tuples with 3 RGB bytes for each pixel,
//   //  with 'height' number of sequential rows, each row having
//   // length of 'width' pixels.
//   renderer.send_frame(image_color)
class TclRenderer {
 public:
  TclRenderer(
      int controller_id, int width, int height, double gamma);

  void Shutdown();

  void SetLayout(const Layout& layout);

  void SetGamma(double gamma);
  void SetGammaRanges(
      int r_min, int r_max, double r_gamma,
      int g_min, int g_max, double g_gamma,
      int b_min, int b_max, double b_gamma);
  void ApplyGamma(Strands* strands);

  void ScheduleImage(uint8_t* image_data, uint64_t time);
  void ScheduleStrands(Strands* strands, uint64_t time);

  Strands* ConvertImageToStrands(uint8_t* image_data);

 private:
  TclRenderer();
  TclRenderer(const TclRenderer& src);
  ~TclRenderer();

  void Run();
  static void* ThreadEntry(void* arg);

  bool Connect();
  bool InitController();
  void SendFrame(uint8_t* frame_data);
  void ConsumeReplyData();

  static uint8_t* ConvertStrandsToFrame(Strands* strands);
  static int BuildFrameColorSeq(
    Strands* strands, int led_id, int color_component, uint8_t* dst);

  int controller_id_;
  int width_;
  int height_;
  bool init_sent_;
  bool is_shutting_down_;
  StrandLayout layout_[STRAND_COUNT];
  double gamma_g_[256];
  double gamma_b_[256];
  Layout layout_;
  int socket_;
};


static const uint8_t MSG_INIT[] = {0xC5, 0x77, 0x88, 0x00, 0x00};
static const double MSG_INIT_DELAY = 0.1;
static const uint8_t MSG_START_FRAME[] = {0xC5, 0x77, 0x88, 0x00, 0x00};
static const double MSG_START_FRAME_DELAY = 0.0005;
static const uint8_t MSG_END_FRAME[] = {0xAA, 0x01, 0x8C, 0x01, 0x55};
static const uint8_t MSG_RESET[] = {0xC2, 0x77, 0x88, 0x00, 0x00};
static const double _MSG_RESET_DELAY = 5;
static const uint8_t MSG_REPLY[] = {0x55, 0x00, 0x00, 0x00, 0x00};

static const uint8_t FRAME_MSG_PREFIX[] = {
    0x88, 0x00, 0x68, 0x3F, 0x2B, 0xFD,
    0x60, 0x8B, 0x95, 0xEF, 0x04, 0x69};
static const uint8_t FRAME_MSG_SUFFIX[] = {0x00, 0x00, 0x00, 0x00};
static const int FRAME_MSG_SIZE = 1024;
static const double FRAME_MSG_DELAY = 0.0015;
static const int FRAME_DATA_LEN = STRAND_LENGTH * 8 * 3;


TclRenderer::TclRenderer(
    int controller_id, int width, int height, double gamma)
    : controller_id_(controller_id), width_(width), height_(height),
      init_sent_(false), is_shutting_down_(false), socket_(-1) {
  set_gamma(gamma);
  memset(layout, 0, sizeof(layout));
}

TclRenderer::~TclRenderer() {
}

void TclRenderer::Shutdown() {
  // TODO(igorc): Join the thread.
}

void TclRenderer::SetLayout(const Layout& layout) {
  Autolock(lock_);
  layout_ = layout;
}

void TclRenderer::SetGamma(double gamma) {
  // 1.0 is uncorrected gamma, which is perceived as "too bright"
  // in the middle. 2.4 is a good starting point. Changing this value
  // affects mid-range pixels - higher values produce dimmer pixels.
  SetGammaRanges(0, 255, gamma, 0, 255, gamma, 0, 255, gamma);
}

void TclRenderer::SetGammaRanges(
    int r_min, int r_max, double r_gamma,
    int g_min, int g_max, double g_gamma,
    int b_min, int b_max, double b_gamma) {
  if (r_min < 0 || r_max > 255 || r_min > r_max || r_gamma < 0.1 ||
      g_min < 0 || g_max > 255 || g_min > g_max || g_gamma < 0.1 ||
      b_min < 0 || b_max > 255 || b_min > b_max || b_gamma < 0.1) {
    fprintf(stderr, "Incorrect gamma values\n");
    return;
  }

  Autolock(lock_);
  for (int i = 0; i < 256; i++) {
    double d = ((double) i) / 255.0;
    gamma_r_[i] =
        (int) (r_min + floor((r_max - r_min) * pow(d, r_gamma) + 0.5));
    gamma_g_[i] =
        (int) (g_min + floor((g_max - g_min) * pow(d, g_gamma) + 0.5));
    gamma_b_[i] =
        (int) (b_min + floor((b_max - b_min) * pow(d, b_gamma) + 0.5));
  }
}

void TclRenderer::ScheduleImage(uint8_t* image_data, uint64_t time) {
  Strands* strands = ConvertImageToStrands(image_data);
  ApplyGamma(strands);
  ScheduleStrands(strands, time);
  delete strands;
}

void TclRenderer::ScheduleStrands(Strands* strands, uint64_t time) {
  uint8_t* frame_data = ConvertStrandsToFrame(strands);

  Autolock(lock_);
  // TODO(igorc): Implement me.
}

Strands* TclRenderer::ConvertImageToStrands(uint8_t* image_data) {
  Autolock(lock_);
  Strands* strands = new Strands();
  for (int strand_id  = 0; strand_id < STRAND_COUNT; strand_id++) {
    int* x = layout_.x[strand_id];
    int* y = layout_.y[strand_id];
    int len = std::min(layout_.lengths[strand_id], STRAND_LENGTH);
    uint8_t* dst_colors = strands->colors[strand_id];
    for (int i = 0; i < len; i++) {
      int color_idx = y[i] * width_ + x[i];
      int dst_idx = i * 3;
      dst_colors[dst_idx] = image_data[color_idx];
      dst_colors[dst_idx + 1] = image_data[color_idx + 1];
      dst_colors[dst_idx + 2] = image_data[color_idx + 2];
    }
    strands->lengths[strand_id] = len;
  }
  return strands;
}

void TclRenderer::ApplyGamma(Strands* strands) {
  Autolock(lock_);
  for (int strand_id  = 0; strand_id < STRAND_COUNT; strand_id++) {
    int len = strands->lengths[strand_id] * 3;
    int8_t* colors = strands->colors[strand_id];
    for (int i = 0; i < len; i += 3) {
      colors[i] = gamma_r_[colors[i]];
      colors[i + 1] = gamma_g_[colors[i + 1]];
      colors[i + 2] = gamma_b_[colors[i + 2]];
    }
  }
}

// static
uint8_t* TclRenderer::ConvertStrandsToFrame(Strands* strands) {
  uint8_t* result = new uint8_t[FRAME_DATA_LEN];
  int pos = 0;
  for (int led_id = 0; led_id < STRAND_LENGTH; led_id++) {
    pos += BuildFrameColorSeq(strands, led_id, 2, result + pos);
    pos += BuildFrameColorSeq(strands, led_id, 1, result + pos);
    pos += BuildFrameColorSeq(strands, led_id, 0, result + pos);
  }
  CHECK(pos == FRAME_DATA_LEN);
  for (int i = 0; i < FRAME_DATA_LEN; i++) {
    // Black color is offset by 0x2C.
    result[i] = (result[i] + 0x2C) & 0xFF;
  }
  return result;
}

// static
int TclRenderer::BuildFrameColorSeq(
    Strands* strands, int led_id, int color_component, uint8_t* dst) {
  int pos = 0;
  int color_bit_mask = 0x80;
  while (color_bit_mask > 0) {
    uint8_t dst_byte = 0;
    for (int strand_id  = 0; strand_id < STRAND_COUNT; strand_id++) {
      if (led_id >= strands.lengths[strand_id])
        continue;
      uint8_t* colors = strands->colors[strand_id];
      uint8_t color = colors[led_id * 3 + color_component];
      if ((color & color_bit_mask) != 0)
        dst_byte |= 1 << strand_id;
    }
    color_bit_mask >>= 1;
    dst[pos++] = dst_byte;
  }
  CHECK(pos == 8);
  return pos;
}

static void Sleep(double seconds) {
  // TODO(igorc): Implement sleep.
}

// static
void* TclRenderer::ThreadEntry(void* arg) {
  TclRenderer* self = reinterpret_cast<TclRenderer*>(arg);
  self->Run();
}

void TclRenderer::Run() {
  while (true) {
    {
      Autolock(lock_);
      if (is_shutting_down_)
        break;
    }

    if (!InitController()) {
      Sleep(1);
      continue;
    }

  }

  if (socket_ != -1)
    close(socket_);
}

bool TclRenderer::Connect() {
  // TODO(igorc): Add interrupt-safe calls and error handling.

  if (socket_ >= 0)
    return true;

  socket_ = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  setblocking(socket_, 0)
  bind(socket_, ('', 0))

  target_ip = ('192.168.60.%s' % (49 + self._controller_id))
  connect(socket_, (target_ip, 5000))
  return true;
}

bool TclRenderer::InitController() {
  // TODO(igorc): Re-init if there's still no reply data in several seconds.
  if (!Connect())
    return false;
  if (init_sent_)
    return true;
  init_sent_ = true;
  // TODO(igorc): Look for a better place for reset.
  send(socket_, MSG_RESET, sizeof(MSG_RESET));
  sleep(MSG_RESET_DELAY);
  send(socket_, MSG_INIT, sizeof(MSG_INIT));
  sleep(MSG_INIT_DELAY);
  return true;
}

void TclRenderer::SendFrame(uint8_t* frame_data) {
  ConsumeReplyData();
  send(socket_, MSG_START_FRAME, sizeof(MSG_START_FRAME));
  Sleep(MSG_START_FRAME_DELAY);

  int message_idx = 0;
  int frame_data_pos = 0;
  while (frame_data_pos < FRAME_DATA_LEN) {
    frame_data_segment = frame_data[frame_data_pos :
                                    frame_data_pos + _FRAME_MSG_SIZE]
    frame_msg = bytearray(_FRAME_MSG_PREFIX)
    frame_msg.extend(frame_data_segment)
    frame_msg.extend(_FRAME_MSG_SUFFIX)
    frame_msg[1] = message_idx
    frame_data_pos += _FRAME_MSG_SIZE
    message_idx += 1
    send(socket_, frame_msg)
    Sleep(FRAME_MSG_DELAY);

    send(socket_, MSG_END_FRAME, sizeof(MSG_END_FRAME));
    ConsumeReplyData();
  }
}

void TclRenderer::ConsumeReplyData() {
  uint8_t buf[65536];
  bool has_reply_data = true;
  while (has_reply_data) {
    recv(socket, buf, sizeof(buf));
    // TODO(igorc): Check error code to set this
    has_reply_data = false;
  }
}

