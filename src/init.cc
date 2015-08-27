#include "FreeType2.h"

void init(v8::Handle<v8::Object> exports) {
  FreeType2::Init(exports);
}

NODE_MODULE(freetype2, init)
