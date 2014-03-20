#include "Glyph.h"

void Glyph::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(New);
  constructorTemplate->SetClassName(NanSymbol("Glyph"));

  v8::Local<v8::ObjectTemplate> constructorObjectTemplate = constructorTemplate->InstanceTemplate();
  constructorObjectTemplate->SetAccessor(NanSymbol("metrics"), acc_metrics);
  constructorObjectTemplate->SetAccessor(NanSymbol("format"), acc_format);
  constructorObjectTemplate->SetAccessor(NanSymbol("lsb_delta"), acc_lsb_delta);
  constructorObjectTemplate->SetAccessor(NanSymbol("rsb_delta"), acc_rsb_delta);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap"), acc_bitmap);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap_left"), acc_bitmap_left);
  constructorObjectTemplate->SetAccessor(NanSymbol("bitmap_top"), acc_bitmap_top);
  constructorObjectTemplate->SetInternalFieldCount(1);

  NanAssignPersistent(v8::Function, constructor, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> Glyph::constructor;

NAN_METHOD(Glyph::New) {
  NanScope();
  Glyph* glyph = new Glyph();
  glyph->Wrap(args.This());
  NanReturnValue(args.This());
}

Glyph::Glyph() {}

Glyph::~Glyph() {}

NAN_GETTER(Glyph::acc_metrics) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  v8::Handle<v8::Object> metrics = v8::Object::New();
  metrics->Set(NanSymbol("width"), v8::Integer::New(glyph->ftGlyph->metrics.width));
  metrics->Set(NanSymbol("height"), v8::Integer::New(glyph->ftGlyph->metrics.height));
  metrics->Set(NanSymbol("horiBearingX"), v8::Integer::New(glyph->ftGlyph->metrics.horiBearingX));
  metrics->Set(NanSymbol("horiBearingY"), v8::Integer::New(glyph->ftGlyph->metrics.horiBearingY));
  metrics->Set(NanSymbol("horiAdvance"), v8::Integer::New(glyph->ftGlyph->metrics.horiAdvance));
  metrics->Set(NanSymbol("vertBearingX"), v8::Integer::New(glyph->ftGlyph->metrics.vertBearingX));
  metrics->Set(NanSymbol("vertBearingY"), v8::Integer::New(glyph->ftGlyph->metrics.vertBearingY));
  metrics->Set(NanSymbol("vertAdvance"), v8::Integer::New(glyph->ftGlyph->metrics.vertAdvance));
  NanReturnValue(metrics);
}

NAN_GETTER(Glyph::acc_format) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(v8::Integer::New(glyph->ftGlyph->format));
}

NAN_GETTER(Glyph::acc_lsb_delta) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(v8::Integer::New(glyph->ftGlyph->lsb_delta));
}

NAN_GETTER(Glyph::acc_rsb_delta) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(v8::Integer::New(glyph->ftGlyph->rsb_delta));
}

NAN_GETTER(Glyph::acc_bitmap) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  v8::Local<v8::Object> bitmap = v8::Object::New();
  bitmap->Set(NanSymbol("rows"), v8::Integer::New(glyph->ftGlyph->bitmap.rows));
  bitmap->Set(NanSymbol("width"), v8::Integer::New(glyph->ftGlyph->bitmap.width));
  bitmap->Set(NanSymbol("pitch"), v8::Integer::New(glyph->ftGlyph->bitmap.pitch));
  bitmap->Set(NanSymbol("buffer"), NanNewBufferHandle((char*)glyph->ftGlyph->bitmap.buffer, glyph->ftGlyph->bitmap.width * glyph->ftGlyph->bitmap.rows));
  bitmap->Set(NanSymbol("num_grays"), v8::Integer::New(glyph->ftGlyph->bitmap.num_grays));
  bitmap->Set(NanSymbol("pixel_mode"), v8::Integer::New(glyph->ftGlyph->bitmap.pixel_mode));
  NanReturnValue(bitmap);
}

NAN_GETTER(Glyph::acc_bitmap_left) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(v8::Integer::New(glyph->ftGlyph->bitmap_left));
}

NAN_GETTER(Glyph::acc_bitmap_top) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(args.This());
  NanReturnValue(v8::Integer::New(glyph->ftGlyph->bitmap_top));
}
