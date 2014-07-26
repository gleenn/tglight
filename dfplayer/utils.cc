// Copyright 2014, Igor Chernyshev.
// Licensed under Apache 2.0 ASF license.
//

#include "utils.h"

#include <GL/gl.h>
#include <GL/glext.h>
#include <errno.h>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

//#include <csignal>

uint64_t GetCurrentMillis() {
  struct timespec time;
  if (clock_gettime(CLOCK_MONOTONIC, &time) == -1) {
    REPORT_ERRNO("clock_gettime(monotonic)");
    CHECK(false);
  }
  return ((uint64_t) time.tv_sec) * 1000 + time.tv_nsec / 1000000;
}

Bytes::Bytes(void* data, int len)
    : data_(NULL), len_(0) {
  SetData(data, len);
}

Bytes::~Bytes() {
  Clear();
}

void Bytes::Clear() {
  if (data_)
    delete[] data_;
  data_ = NULL;
  len_ = 0;
}

void Bytes::SetData(void* data, int len) {
  Clear();
  data_ = new uint8_t[len];
  memcpy(data_, data, len);
  len_ = len;
}

// Resizes image using bilinear interpolation.
uint8_t* ResizeImage(
    uint8_t* src, int src_w, int src_h, int dst_w, int dst_h) {
  cv::Mat src_img(src_h, src_w, CV_8UC3, src);
  cv::Mat dst_img(cv::Size(dst_w, dst_h), CV_8UC3);
  cv::resize(src_img, dst_img, dst_img.size());
  dst_img = dst_img.clone();  // Make it contiguous
  int dst_len = dst_w * dst_h * 3;
  uint8_t* dst = new uint8_t[dst_len];
  memcpy(dst, dst_img.data, dst_len);
  return dst;
}

uint8_t* FlipImage(uint8_t* src, int w, int h) {
  cv::Mat src_img(h, w, CV_8UC3, src);
  cv::Mat dst_img(cv::Size(w, h), CV_8UC3);
  cv::flip(src_img, dst_img, 1);
  int dst_len = w * h * 3;
  uint8_t* dst = new uint8_t[dst_len];
  memcpy(dst, dst_img.data, dst_len);
  return dst;
}

void PasteSubImage(
    uint8_t* src, int src_w, int src_h,
    uint8_t* dst, int dst_x, int dst_y, int dst_w, int dst_h) {
  for (int y = 0; y < src_h; y++) {
    int y2 = dst_y + y;
    if (y2 >= dst_h)
      break;
    for (int x = 0; x < src_w; x++) {
      int x2 = dst_x + x;
      if (x2 >= dst_w)
        break;
      int src_pos = (y * src_w + x) * 3;
      int dst_pos = (y2 * dst_w + x2) * 3;
      dst[dst_pos] = src[src_pos];
      dst[dst_pos + 1] = src[src_pos + 1];
      dst[dst_pos + 2] = src[src_pos + 2];
    }
  }
}

