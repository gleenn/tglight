# -*- coding: utf-8 -*-

from ..effect import Effect, register
from ..util import hsl2rgb


class Chameleon(Effect):

  def __init__(self, duration=30):
    Effect.__init__(self, duration=duration)

  def get_image(self, elapsed):
    hsl = (360 * elapsed / self._duration, 1, 0.5)
    rgb = hsl2rgb(*hsl)
    return self._create_image(rgb, 255)


register('chameleon', Chameleon)
