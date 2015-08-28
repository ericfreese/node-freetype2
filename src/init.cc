#include "FreeType2.h"

NAN_MODULE_INIT(init) {
  FreeType2::Init(target);
}

NODE_MODULE(freetype2, init)
