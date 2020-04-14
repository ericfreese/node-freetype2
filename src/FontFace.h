#ifndef NODE_FREETYPE2_FONTFACE_H
#define NODE_FREETYPE2_FONTFACE_H

#include "util.h"
// #include "GlyphSlot.h"

// #include <vector>

class FontFace : public Napi::ObjectWrap<FontFace> {
  public:
    FT_Face ftFace;
    FT_Byte* data;

    static Napi::FunctionReference constructor;

    FontFace(const Napi::CallbackInfo& info);
    static void Initialize(Napi::Env& env);

    ~FontFace();

  private:
    // Napi::Value GetNumFaces(const Napi::CallbackInfo &info);
    // Napi::Value GetFaceIndex(const Napi::CallbackInfo &info);
    Napi::Value GetProperties(const Napi::CallbackInfo &info);

    Napi::Value SetCharSize(const Napi::CallbackInfo &info);
    Napi::Value SetPixelSizes(const Napi::CallbackInfo &info);
    Napi::Value RequestSize(const Napi::CallbackInfo &info);
    Napi::Value SelectSize(const Napi::CallbackInfo &info);
    Napi::Value SetTransform(const Napi::CallbackInfo &info);
    Napi::Value LoadGlyph(const Napi::CallbackInfo &info);
    Napi::Value GetCharIndex(const Napi::CallbackInfo &info);
    Napi::Value GetFirstChar(const Napi::CallbackInfo &info);
    Napi::Value GetNextChar(const Napi::CallbackInfo &info);

};

#endif
