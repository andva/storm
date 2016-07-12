#include "color.h"
using namespace hscore;

const Color	COLOR_WHITE = Color(0xFF, 0xFF, 0xFF);
const Color	COLOR_BLACK = Color(0x00, 0x00, 0x00);
const Color	COLOR_GRAY = Color(0x7F, 0x7F, 0x7F);
const Color	COLOR_LIGHT_GRAY = Color(0xC0, 0xC0, 0xC0);

const Color	COLOR_RED = Color(0xFF, 0x00, 0x00);
const Color	COLOR_GREEN = Color(0x00, 0xFF, 0x00);
const Color	COLOR_BLUE = Color(0x00, 0x00, 0xFF);

const Color	COLOR_DARK_RED = Color(0x7F, 0x00, 0x00);
const Color	COLOR_DARK_GREEN = Color(0x00, 0x7F, 0x00);
const Color	COLOR_DARK_BLUE = Color(0x00, 0x00, 0x7F);

const Color	COLOR_LIGHT_RED = Color(0xFF, 0x7F, 0x7F);
const Color	COLOR_LIGHT_GREEN = Color(0x7F, 0xFF, 0x7F);
const Color	COLOR_LIGHT_BLUE = Color(0x7F, 0x7F, 0xFF);

const Color	COLOR_CYAN = Color(0x00, 0xFF, 0xFF);
const Color	COLOR_MAGENTA = Color(0xFF, 0x00, 0xFF);
const Color	COLOR_YELLOW = Color(0xFF, 0xFF, 0x00);

bool hscore::operator==(const Color &ca, const Color &cb)
{
  return ca.r == cb.r && ca.g == cb.g && ca.b == cb.b;
}
