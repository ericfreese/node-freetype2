#ifndef NODE_FREETYPE2_GLYPH_H
#define NODE_FREETYPE2_GLYPH_H

#include "FreeType2.h"
#include "FontFace.h"

#include FT_BITMAP_H

class Glyph : public node::ObjectWrap {
  public:
    explicit Glyph();
    ~Glyph();

    static void Init(v8::Handle<v8::Object>);
    static v8::Persistent<v8::Function> constructor;
    static NAN_METHOD(New);

    FT_GlyphSlot ftGlyph;

  private:
    static NAN_GETTER(acc_metrics);
    static NAN_GETTER(acc_format);
    static NAN_GETTER(acc_lsb_delta);
    static NAN_GETTER(acc_rsb_delta);
    static NAN_GETTER(acc_bitmap);
    static NAN_GETTER(acc_bitmap_left);
    static NAN_GETTER(acc_bitmap_top);

};

#endif