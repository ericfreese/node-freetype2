#ifndef NODE_FREETYPE2_GLYPHSLOT_H
#define NODE_FREETYPE2_GLYPHSLOT_H

#include "FreeType2.h"

#include FT_BITMAP_H

class GlyphSlot : public node::ObjectWrap {
  public:
    static v8::Local<v8::Function> GetConstructor();
    FT_GlyphSlot ftGlyphSlot;

  private:
    explicit GlyphSlot();
    ~GlyphSlot();

    static NAN_METHOD(New);
    static v8::Local<v8::FunctionTemplate> CreateConstructorTemplate();
    static Nan::Persistent<v8::Function> constructor;

    static NAN_GETTER(acc_metrics);
    static NAN_GETTER(acc_format);
    static NAN_GETTER(acc_bitmap);
    static NAN_GETTER(acc_bitmap_left);
    static NAN_GETTER(acc_bitmap_top);
    static NAN_GETTER(acc_lsb_delta);
    static NAN_GETTER(acc_rsb_delta);
};

#endif
