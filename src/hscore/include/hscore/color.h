#ifndef HSCORE_COLOR_H
#define HSCORE_COLOR_H

#pragma once

#include <hscore/linmath.h>

namespace hscore
{
  struct Color
  {
    unsigned char r;
    unsigned char g;
    unsigned char b;

    Color() : r(0xFF), g(0xFF), b(0xFF) {}
    Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

    void set(unsigned char _r, unsigned char _g, unsigned char _b)
    {
      r = _r;	g = _g;	b = _b;
    }

    void set(const Color&	color)
    {
      r = color.r;
      g = color.g;
      b = color.b;
    }

    vec3 getFVec() const { return vec3(float_t(r) / 255.0f, float_t(g) / 255.0f, float_t(b) / 255.0f); }
  };
  bool operator== (const Color &ca, const Color &cb);
}

extern const hscore::Color	COLOR_WHITE;
extern const hscore::Color	COLOR_BLACK;
extern const hscore::Color	COLOR_GRAY;
extern const hscore::Color	COLOR_LIGHT_GRAY;

extern const hscore::Color	COLOR_RED;
extern const hscore::Color	COLOR_GREEN;
extern const hscore::Color	COLOR_BLUE;

extern const hscore::Color	COLOR_DARK_RED;
extern const hscore::Color	COLOR_DARK_GREEN;
extern const hscore::Color	COLOR_DARK_BLUE;

extern const hscore::Color	COLOR_LIGHT_RED;
extern const hscore::Color	COLOR_LIGHT_GREEN;
extern const hscore::Color	COLOR_LIGHT_BLUE;

extern const hscore::Color	COLOR_CYAN;
extern const hscore::Color	COLOR_MAGENTA;
extern const hscore::Color	COLOR_YELLOW;

#endif