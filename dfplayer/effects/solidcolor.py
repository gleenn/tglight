# -*- coding: utf-8 -*-

from ..effect import Effect, register

class SolidColor(Effect):

  def __init__(self, duration=20, color='#00FF00'):
    Effect.__init__(self, duration=duration)
    self._color = color

  def get_image(self, elapsed):
    return self._create_image(self._color, 255)


register('solidcolor', SolidColor)
