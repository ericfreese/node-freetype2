#ifndef NODE_FREETYPE2_FONTFACE_H
#define NODE_FREETYPE2_FONTFACE_H

#include "util.h"

class FontFace : public Napi::ObjectWrap<FontFace> {
  public:
    FT_Face ftFace;
    Napi::Reference<Napi::Buffer<FT_Byte>> bufferRef;

    FontFace(const Napi::CallbackInfo& info);
    static Napi::FunctionReference Initialize(Napi::Env& env);

    ~FontFace();

  private:
    Napi::Value GetProperties(const Napi::CallbackInfo &info);

    Napi::Value SetCharSize(const Napi::CallbackInfo &info);
    Napi::Value SetPixelSizes(const Napi::CallbackInfo &info);
    // Napi::Value RequestSize(const Napi::CallbackInfo &info);
    Napi::Value SelectSize(const Napi::CallbackInfo &info);
    Napi::Value SetTransform(const Napi::CallbackInfo &info);
    Napi::Value LoadGlyph(const Napi::CallbackInfo &info);
    Napi::Value GetCharIndex(const Napi::CallbackInfo &info);
    Napi::Value GetFirstChar(const Napi::CallbackInfo &info);
    Napi::Value GetNextChar(const Napi::CallbackInfo &info);
    // Napi::Value GetGetNameIndex(const Napi::CallbackInfo &info);
    Napi::Value LoadChar(const Napi::CallbackInfo &info);
    Napi::Value RenderGlyph(const Napi::CallbackInfo &info);
    Napi::Value GetKerning(const Napi::CallbackInfo &info);
    // Napi::Value GetTrackKerning(const Napi::CallbackInfo &info);
    // Napi::Value GetGlyphName(const Napi::CallbackInfo &info);
    // Napi::Value GetPostscriptName(const Napi::CallbackInfo &info);
    // Napi::Value SelectCharmap(const Napi::CallbackInfo &info);
    // Napi::Value SetCharmap(const Napi::CallbackInfo &info);
    // Napi::Value GetCharmapIndex(const Napi::CallbackInfo &info);
    // Napi::Value GetFSTypeFlags(const Napi::CallbackInfo &info);
    // Napi::Value GetSubGlyphInfo(const Napi::CallbackInfo &info);

};

#endif
