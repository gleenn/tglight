# -*- coding: utf-8 -*-
#
# Controls TCL controller.

from .stats import Stats
from .tcl_layout import TclLayout
from .tcl_renderer_py import TclRenderer as TclPyImpl
from .tcl_renderer_cc import Layout as TclCcLayout
from .tcl_renderer_cc import TclRenderer as TclCcImpl
from .tcl_renderer_cc import Time as TclCcTime
from .util import get_time_millis

_USE_CC_IMPL = True

class TclRenderer(object):
  """To use this class:
       renderer = TclRenderer(controller_id, width, height, 'layout.dxf', 2.4)
       # 'image_colors' has tuples with 3 RGB bytes for each pixel,
       # with 'height' number of sequential rows, each row having
       # length of 'width' pixels.
       renderer.send_frame(image_data)
  """

  def __init__(self, controller_id, width, height, layout_file, gamma):
    self._layout = TclLayout(layout_file, width - 1, height - 1)
    self._use_cc_impl = _USE_CC_IMPL
    if self._use_cc_impl:
      layout = TclCcLayout()
      for s in self._layout.get_strands():
        for c in s.get_coords():
          layout.AddCoord(s.get_id(), c[0], c[1])
      self._renderer = TclCcImpl(controller_id, width, height, layout, gamma)
      self._frame_send_duration = self._renderer.GetFrameSendDuration()
      # self._renderer.SetAutoResetAfterNoDataMs(0)
    else:
      self._renderer = TclPyImpl(controller_id, width, height, self._layout)
      self._frame_send_duration = self._renderer.get_send_duration_ms()
    self.set_gamma(gamma)
    self._frame_delays = []
    self._frame_delays_clear_time = get_time_millis()

  def get_layout_coords(self):
    return self._layout.get_all_coords()

  def set_gamma(self, gamma):
    # 1.0 is uncorrected gamma, which is perceived as "too bright"
    # in the middle. 2.4 is a good starting point. Changing this value
    # affects mid-range pixels - higher values produce dimmer pixels.
    self.set_gamma_ranges((0, 255, gamma), (0, 255, gamma), (0, 255, gamma))

  def set_gamma_ranges(self, r, g, b):
    if self._use_cc_impl:
      self._renderer.SetGammaRanges(
          r[0], r[1], r[2], g[0], g[1], g[2], b[0], b[1], b[2])
    else:
      self._renderer.set_gamma_ranges(r, g, b)

  def has_scheduling_support(self):
    return self._use_cc_impl

  def get_send_duration_ms(self):
    return self._frame_send_duration

  def send_frame(self, image, delay_ms):
    if self._use_cc_impl:
      time = TclCcTime()
      time.AddMillis(delay_ms - self._frame_send_duration)
      self._renderer.ScheduleImageAt(image.tostring(), time)
    else:
      self._renderer.send_frame(list(image.getdata()), get_time_millis())

  def get_and_clear_frame_delays(self):
    self._populate_frame_delays()
    result = self._frame_delays
    duration = get_time_millis() - self._frame_delays_clear_time
    self._frame_delays = []
    self._frame_delays_clear_time = get_time_millis()
    return (duration, result)

  def _populate_frame_delays(self):
    if self._use_cc_impl:
      for d in self._renderer.GetAndClearFrameDelays():
        self._frame_delays.append(d)
    else:
      for d in self._renderer.get_and_clear_frame_delays():
        # Pretent that sending had no delays as we currently
        # have no way to compensate for that.
        d -= self._frame_send_duration
        self._frame_delays.append(d if d > 0 else 0)

