/*
  Custom effect that creates a Larson Scanner with rainbow colors
  It has two modes:
  1) if the segment options parameter is set to NO_OPTIONS, then
    the rainbow of colors span the 'comet'.
  2) if the segment options parameter is set to a FADE option
    (e.g. FADE_MEDIUM), then the rainbow of colors span the segment
    and the 'comet' merely shows the colors at that point in the segment.
  
  Keith Lord - 2018

  LICENSE

  The MIT License (MIT)

  Copyright (c) 2018  Keith Lord 

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sub-license, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
  
  CHANGELOG
  2018-08-26 initial version
*/

#ifndef RainbowLarson_h
#define RainbowLarson_h

#include <WS2812FX.h>

extern WS2812FX ws2812fx;

uint16_t rainbowLarson(void) {
  WS2812FX::Segment* seg = ws2812fx.getSegment(); // get the current segment
  int seglen = seg->stop - seg->start + 1;

  static int16_t index = 0, dir = 1, cnt = 0;
  index += dir;

  ws2812fx.fade_out();

  if(seg->options == NO_OPTIONS) {
    ws2812fx.setPixelColor(seg->start + index, ws2812fx.color_wheel((cnt++ % 8) * 32));
  } else {
    ws2812fx.setPixelColor(seg->start + index, ws2812fx.color_wheel((index * 256) / seglen));
  }

  if(index >= (seg->stop - seg->start) || index <= 0) dir = -dir; 

  return (seg->speed / (seglen * 2));
}

#endif
