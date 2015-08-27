#include "GlyphSlot.h"

void GlyphSlot::Init(v8::Handle<v8::Object> exports) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(isolate, New);
  constructorTemplate->SetClassName(v8::String::NewFromUtf8(isolate, "GlyphSlot"));

  v8::Local<v8::ObjectTemplate> instanceTemplate = constructorTemplate->InstanceTemplate();
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "metrics"), acc_metrics);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "format"), acc_format);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "bitmap"), acc_bitmap);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "bitmap_left"), acc_bitmap_left);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "bitmap_top"), acc_bitmap_top);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "lsb_delta"), acc_lsb_delta);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "rsb_delta"), acc_rsb_delta);
  instanceTemplate->SetInternalFieldCount(1);

  constructor.Reset(isolate, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> GlyphSlot::constructor;

void GlyphSlot::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  GlyphSlot* glyphSlot = new GlyphSlot();
  glyphSlot->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

void GlyphSlot::acc_metrics(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  v8::Handle<v8::Object> metrics = v8::Object::New(isolate);
  metrics->Set(v8::String::NewFromUtf8(isolate, "width"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.width));
  metrics->Set(v8::String::NewFromUtf8(isolate, "height"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.height));
  metrics->Set(v8::String::NewFromUtf8(isolate, "horiBearingX"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.horiBearingX));
  metrics->Set(v8::String::NewFromUtf8(isolate, "horiBearingY"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.horiBearingY));
  metrics->Set(v8::String::NewFromUtf8(isolate, "horiAdvance"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.horiAdvance));
  metrics->Set(v8::String::NewFromUtf8(isolate, "vertBearingX"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.vertBearingX));
  metrics->Set(v8::String::NewFromUtf8(isolate, "vertBearingY"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.vertBearingY));
  metrics->Set(v8::String::NewFromUtf8(isolate, "vertAdvance"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->metrics.vertAdvance));
  info.GetReturnValue().Set(metrics);
}

void GlyphSlot::acc_format(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), glyphSlot->ftGlyphSlot->format));
}

void GlyphSlot::acc_bitmap(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  v8::Local<v8::Object> bitmap = v8::Object::New(isolate);
  bitmap->Set(v8::String::NewFromUtf8(isolate, "rows"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.rows));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "width"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.width));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "pitch"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.pitch));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "buffer"), node::Buffer::New(isolate, (char*)glyphSlot->ftGlyphSlot->bitmap.buffer, glyphSlot->ftGlyphSlot->bitmap.width * glyphSlot->ftGlyphSlot->bitmap.rows));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "num_grays"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.num_grays));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "pixel_mode"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.pixel_mode));
  bitmap->Set(v8::String::NewFromUtf8(isolate, "palette_mode"), v8::Integer::New(isolate, glyphSlot->ftGlyphSlot->bitmap.palette_mode));
  info.GetReturnValue().Set(bitmap);
}

void GlyphSlot::acc_bitmap_left(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), glyphSlot->ftGlyphSlot->bitmap_left));
}

void GlyphSlot::acc_bitmap_top(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), glyphSlot->ftGlyphSlot->bitmap_top));
}

void GlyphSlot::acc_lsb_delta(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), glyphSlot->ftGlyphSlot->lsb_delta));
}

void GlyphSlot::acc_rsb_delta(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), glyphSlot->ftGlyphSlot->rsb_delta));
}
