#ifndef NODE_FREETYPE2_FONTFACE_H
#define NODE_FREETYPE2_FONTFACE_H

#include "util.h"
// #include "GlyphSlot.h"

// #include <vector>

class FontFace : public Napi::ObjectWrap<FontFace> {
  public:
    // static v8::Local<v8::Function> GetConstructor();
    FT_Face ftFace;
    FT_Byte* data;

    static Napi::FunctionReference constructor;

    FontFace(const Napi::CallbackInfo& info);
    static void Initialize(Napi::Env& env);

    ~FontFace();

  private:
    Napi::Value GetNumFaces(const Napi::CallbackInfo &info);
    Napi::Value GetFaceIndex(const Napi::CallbackInfo &info);

    Napi::Value GetCharIndex(const Napi::CallbackInfo &info);

    // static NAN_GETTER(acc_face_flags);
    // static NAN_GETTER(acc_style_flags);
    // static NAN_GETTER(acc_num_glyphs);
    // static NAN_GETTER(acc_family_name);
    // static NAN_GETTER(acc_style_name);
    // static NAN_GETTER(acc_available_sizes);
    // static NAN_GETTER(acc_charmaps);
    // static NAN_GETTER(acc_bbox);
    // static NAN_GETTER(acc_units_per_EM);
    // static NAN_GETTER(acc_ascender);
    // static NAN_GETTER(acc_descender);
    // static NAN_GETTER(acc_height);
    // static NAN_GETTER(acc_max_advance_width);
    // static NAN_GETTER(acc_max_advance_height);
    // static NAN_GETTER(acc_underline_position);
    // static NAN_GETTER(acc_underline_thickness);
    // static NAN_GETTER(acc_glyph);
};

#endif
