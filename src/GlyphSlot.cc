#include "GlyphSlot.h"

void GlyphSlot::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(New);
  constructorTemplate->SetClassName(NanSymbol("GlyphSlot"));

  v8::Local<v8::ObjectTemplate> constructorObjectTemplate = constructorTemplate->InstanceTemplate();
  constructorObjectTemplate->SetAccessor(NanSymbol("metrics"), acc_metrics);
  constructorObjectTemplate->SetAccessor(NanSymbol("format"), acc_format);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap"), acc_bitmap);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap_left"), acc_bitmap_left);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap_top"), acc_bitmap_top);
  constructorObjectTemplate->SetAccessor(NanSymbol("lsb_delta"), acc_lsb_delta);
  constructorObjectTemplate->SetAccessor(NanSymbol("rsb_delta"), acc_rsb_delta);
  constructorObjectTemplate->SetInternalFieldCount(1);

  NanAssignPersistent(v8::Function, constructor, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> GlyphSlot::constructor;

NAN_METHOD(GlyphSlot::New) {
  NanScope();
  GlyphSlot* glyphSlot = new GlyphSlot();
  glyphSlot->Wrap(args.This());
  NanReturnValue(args.This());
}

GlyphSlot::GlyphSlot() {}

GlyphSlot::~GlyphSlot() {}

NAN_GETTER(GlyphSlot::acc_metrics) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  v8::Handle<v8::Object> metrics = v8::Object::New();
  metrics->Set(NanSymbol("width"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.width));
  metrics->Set(NanSymbol("height"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.height));
  metrics->Set(NanSymbol("horiBearingX"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.horiBearingX));
  metrics->Set(NanSymbol("horiBearingY"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.horiBearingY));
  metrics->Set(NanSymbol("horiAdvance"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.horiAdvance));
  metrics->Set(NanSymbol("vertBearingX"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.vertBearingX));
  metrics->Set(NanSymbol("vertBearingY"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.vertBearingY));
  metrics->Set(NanSymbol("vertAdvance"), v8::Integer::New(glyphSlot->ftGlyphSlot->metrics.vertAdvance));
  NanReturnValue(metrics);
}

NAN_GETTER(GlyphSlot::acc_format) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  NanReturnValue(v8::Integer::New(glyphSlot->ftGlyphSlot->format));
}

NAN_GETTER(GlyphSlot::acc_bitmap) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  v8::Local<v8::Object> bitmap = v8::Object::New();
  bitmap->Set(NanSymbol("rows"), v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap.rows));
  bitmap->Set(NanSymbol("width"), v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap.width));
  bitmap->Set(NanSymbol("pitch"), v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap.pitch));
  bitmap->Set(NanSymbol("buffer"), NanNewBufferHandle((char*)glyphSlot->ftGlyphSlot->bitmap.buffer, glyphSlot->ftGlyphSlot->bitmap.width * glyphSlot->ftGlyphSlot->bitmap.rows));
  bitmap->Set(NanSymbol("num_grays"), v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap.num_grays));
  bitmap->Set(NanSymbol("pixel_mode"), v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap.pixel_mode));
  NanReturnValue(bitmap);
}

NAN_GETTER(GlyphSlot::acc_bitmap_left) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  NanReturnValue(v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap_left));
}

NAN_GETTER(GlyphSlot::acc_bitmap_top) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  NanReturnValue(v8::Integer::New(glyphSlot->ftGlyphSlot->bitmap_top));
}

NAN_GETTER(GlyphSlot::acc_lsb_delta) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  NanReturnValue(v8::Integer::New(glyphSlot->ftGlyphSlot->lsb_delta));
}

NAN_GETTER(GlyphSlot::acc_rsb_delta) {
  NanScope();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(args.This());
  NanReturnValue(v8::Integer::New(glyphSlot->ftGlyphSlot->rsb_delta));
}
