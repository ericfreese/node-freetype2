#include <nan.h>

#include "FontFace.h"
#include "FreeType2.h"

void init(v8::Handle<v8::Object> exports) {
  NanScope();

  FreeType2::Init(exports);
}

NODE_MODULE(freetype2, init)
