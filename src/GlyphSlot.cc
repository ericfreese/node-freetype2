#include "GlyphSlot.h"

Nan::Persistent<v8::Function> GlyphSlot::constructor;

v8::Local<v8::FunctionTemplate> GlyphSlot::CreateConstructorTemplate() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> constructorTemplate = Nan::New<v8::FunctionTemplate>(New);
  constructorTemplate->SetClassName(Nan::New("GlyphSlot").ToLocalChecked());

  v8::Local<v8::ObjectTemplate> instanceTemplate = constructorTemplate->InstanceTemplate();
  Nan::SetAccessor(instanceTemplate, Nan::New("metrics").ToLocalChecked(), acc_metrics);
  Nan::SetAccessor(instanceTemplate, Nan::New("format").ToLocalChecked(), acc_format);
  Nan::SetAccessor(instanceTemplate, Nan::New("bitmap").ToLocalChecked(), acc_bitmap);
  Nan::SetAccessor(instanceTemplate, Nan::New("bitmap_left").ToLocalChecked(), acc_bitmap_left);
  Nan::SetAccessor(instanceTemplate, Nan::New("bitmap_top").ToLocalChecked(), acc_bitmap_top);
  Nan::SetAccessor(instanceTemplate, Nan::New("lsb_delta").ToLocalChecked(), acc_lsb_delta);
  Nan::SetAccessor(instanceTemplate, Nan::New("rsb_delta").ToLocalChecked(), acc_rsb_delta);
  instanceTemplate->SetInternalFieldCount(1);

  return scope.Escape(constructorTemplate);
}

v8::Local<v8::Function> GlyphSlot::GetConstructor() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::Function> localConstructor;

  if (constructor.IsEmpty()) {
    localConstructor = Nan::GetFunction(CreateConstructorTemplate()).ToLocalChecked();
    constructor.Reset(localConstructor);
  } else {
    localConstructor = Nan::New(constructor);
  }

  return scope.Escape(localConstructor);
}

NAN_METHOD(GlyphSlot::New) {
  GlyphSlot* glyphSlot = new GlyphSlot();
  glyphSlot->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

GlyphSlot::GlyphSlot() {}

GlyphSlot::~GlyphSlot() {}

NAN_GETTER(GlyphSlot::acc_metrics) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  v8::Local<v8::Object> metrics = Nan::New<v8::Object>();
  Nan::Set(metrics, Nan::New("width").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.width));
  Nan::Set(metrics, Nan::New("height").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.height));
  Nan::Set(metrics, Nan::New("horiBearingX").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.horiBearingX));
  Nan::Set(metrics, Nan::New("horiBearingY").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.horiBearingY));
  Nan::Set(metrics, Nan::New("horiAdvance").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.horiAdvance));
  Nan::Set(metrics, Nan::New("vertBearingX").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.vertBearingX));
  Nan::Set(metrics, Nan::New("vertBearingY").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.vertBearingY));
  Nan::Set(metrics, Nan::New("vertAdvance").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->metrics.vertAdvance));
  info.GetReturnValue().Set(metrics);
}

NAN_GETTER(GlyphSlot::acc_format) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)glyphSlot->ftGlyphSlot->format));
}

NAN_GETTER(GlyphSlot::acc_bitmap) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());

  v8::Local<v8::Object> bitmap = Nan::New<v8::Object>();
  Nan::Set(bitmap, Nan::New("rows").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap.rows));
  Nan::Set(bitmap, Nan::New("width").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap.width));
  Nan::Set(bitmap, Nan::New("pitch").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap.pitch));
  Nan::Set(bitmap, Nan::New("buffer").ToLocalChecked(), Nan::CopyBuffer((char*)glyphSlot->ftGlyphSlot->bitmap.buffer, glyphSlot->ftGlyphSlot->bitmap.pitch * glyphSlot->ftGlyphSlot->bitmap.rows).ToLocalChecked());
  Nan::Set(bitmap, Nan::New("num_grays").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap.num_grays));
  Nan::Set(bitmap, Nan::New("pixel_mode").ToLocalChecked(), Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap.pixel_mode));

  info.GetReturnValue().Set(bitmap);
}

NAN_GETTER(GlyphSlot::acc_bitmap_left) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap_left));
}

NAN_GETTER(GlyphSlot::acc_bitmap_top) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)glyphSlot->ftGlyphSlot->bitmap_top));
}

NAN_GETTER(GlyphSlot::acc_lsb_delta) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)glyphSlot->ftGlyphSlot->lsb_delta));
}

NAN_GETTER(GlyphSlot::acc_rsb_delta) {
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)glyphSlot->ftGlyphSlot->rsb_delta));
}
