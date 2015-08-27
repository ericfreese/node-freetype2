#ifndef NODE_FREETYPE2_GLYPHSLOT_H
#define NODE_FREETYPE2_GLYPHSLOT_H

#include "FreeType2.h"
#include "FontFace.h"

#include FT_BITMAP_H

class GlyphSlot : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object>);
    static v8::Persistent<v8::Function> constructor;

    FT_GlyphSlot ftGlyphSlot;

  private:
    static void New(const v8::FunctionCallbackInfo<v8::Value>& args);

    static void acc_metrics(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_format(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_bitmap(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_bitmap_left(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_bitmap_top(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_lsb_delta(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
    static void acc_rsb_delta(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info);
};

#endif
