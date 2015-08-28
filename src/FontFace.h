#ifndef NODE_FREETYPE2_FONTFACE_H
#define NODE_FREETYPE2_FONTFACE_H

#include "FreeType2.h"
#include "GlyphSlot.h"

#include <vector>

class FontFace : public node::ObjectWrap {
  public:
    static v8::Local<v8::Function> GetConstructor();
    FT_Face ftFace;

  private:
    explicit FontFace();
    ~FontFace();

    static NAN_METHOD(New);
    static v8::Local<v8::FunctionTemplate> CreateConstructorTemplate();
    static Nan::Persistent<v8::Function> constructor;

    static NAN_GETTER(acc_num_faces);
    static NAN_GETTER(acc_face_index);
    static NAN_GETTER(acc_face_flags);
    static NAN_GETTER(acc_style_flags);
    static NAN_GETTER(acc_num_glyphs);
    static NAN_GETTER(acc_family_name);
    static NAN_GETTER(acc_style_name);
    static NAN_GETTER(acc_num_fixed_sizes);
    static NAN_GETTER(acc_available_sizes);
    static NAN_GETTER(acc_num_charmaps);
    static NAN_GETTER(acc_charmaps);
    static NAN_GETTER(acc_bbox);
    static NAN_GETTER(acc_units_per_EM);
    static NAN_GETTER(acc_ascender);
    static NAN_GETTER(acc_descender);
    static NAN_GETTER(acc_height);
    static NAN_GETTER(acc_max_advance_width);
    static NAN_GETTER(acc_max_advance_height);
    static NAN_GETTER(acc_underline_position);
    static NAN_GETTER(acc_underline_thickness);
    static NAN_GETTER(acc_glyph);
};

#endif
