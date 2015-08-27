#ifndef NODE_FREETYPE2_FONTFACE_H
#define NODE_FREETYPE2_FONTFACE_H

#include "FreeType2.h"
#include "GlyphSlot.h"

#include <vector>

class FontFace : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object>);
    static v8::Persistent<v8::Function> constructor;

    FT_Face ftFace;

  private:
    explicit FontFace();
    ~FontFace();

    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void acc_num_faces(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_face_index(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_face_flags(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_style_flags(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_num_glyphs(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_family_name(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_style_name(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_num_fixed_sizes(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_available_sizes(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_num_charmaps(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_charmaps(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_bbox(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_units_per_EM(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_ascender(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_descender(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_height(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_max_advance_width(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_max_advance_height(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_underline_position(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_underline_thickness(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_glyph(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
};

#endif
