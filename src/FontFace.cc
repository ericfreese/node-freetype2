#include "FontFace.h"

void FontFace::Init(v8::Handle<v8::Object> exports) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(isolate, New);
  constructorTemplate->SetClassName(v8::String::NewFromUtf8(isolate, "FontFace"));

  v8::Local<v8::ObjectTemplate> instanceTemplate = constructorTemplate->InstanceTemplate();
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "num_faces"), acc_num_faces);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "face_index"), acc_face_index);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "face_flags"), acc_face_flags);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "style_flags"), acc_style_flags);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "num_glyphs"), acc_num_glyphs);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "family_name"), acc_family_name);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "style_name"), acc_style_name);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "num_fixed_sizes"), acc_num_fixed_sizes);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "available_sizes"), acc_available_sizes);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "num_charmaps"), acc_num_charmaps);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "charmaps"), acc_charmaps);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "bbox"), acc_bbox);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "units_per_EM"), acc_units_per_EM);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "ascender"), acc_ascender);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "descender"), acc_descender);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "height"), acc_height);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "max_advance_width"), acc_max_advance_width);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "max_advance_height"), acc_max_advance_height);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "underline_position"), acc_underline_position);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "underline_thickness"), acc_underline_thickness);
  instanceTemplate->SetAccessor(v8::String::NewFromUtf8(isolate, "glyph"), acc_glyph);
  instanceTemplate->SetInternalFieldCount(1);

  constructor.Reset(isolate, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> FontFace::constructor;

void FontFace::New(const v8::FunctionCallbackInfo<v8::Value>& args) {
  FontFace* fontFace = new FontFace();
  fontFace->Wrap(args.This());
  args.GetReturnValue().Set(args.This());
}

FontFace::FontFace() {}

FontFace::~FontFace() {
  FT_Done_Face(this->ftFace);
}

void FontFace::acc_num_faces(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->num_faces));
}

void FontFace::acc_face_index(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->face_index));
}

void FontFace::acc_face_flags(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->face_flags));
}

void FontFace::acc_style_flags(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->style_flags));
}

void FontFace::acc_num_glyphs(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->num_glyphs));
}

void FontFace::acc_family_name(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), fontFace->ftFace->family_name));
}

void FontFace::acc_style_name(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), fontFace->ftFace->style_name));
}

void FontFace::acc_num_fixed_sizes(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->num_fixed_sizes));
}

void FontFace::acc_available_sizes(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Handle<v8::Array> available_sizes = v8::Array::New(isolate, fontFace->ftFace->num_fixed_sizes);

  for (int i = 0; i < fontFace->ftFace->num_fixed_sizes; i++) {
    v8::Handle<v8::Object> size = v8::Object::New(isolate);
    size->Set(v8::String::NewFromUtf8(isolate, "height"), v8::Integer::New(isolate, fontFace->ftFace->available_sizes[i].height));
    size->Set(v8::String::NewFromUtf8(isolate, "width"), v8::Integer::New(isolate, fontFace->ftFace->available_sizes[i].width));
    size->Set(v8::String::NewFromUtf8(isolate, "size"), v8::Number::New(isolate, fontFace->ftFace->available_sizes[i].size));
    size->Set(v8::String::NewFromUtf8(isolate, "x_ppem"), v8::Number::New(isolate, fontFace->ftFace->available_sizes[i].x_ppem));
    size->Set(v8::String::NewFromUtf8(isolate, "y_ppem"), v8::Number::New(isolate, fontFace->ftFace->available_sizes[i].y_ppem));
    available_sizes->Set(i, size);
  }

  info.GetReturnValue().Set(available_sizes);
}

void FontFace::acc_num_charmaps(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->num_charmaps));
}

void FontFace::acc_charmaps(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Handle<v8::Array> charmaps = v8::Array::New(isolate, fontFace->ftFace->num_charmaps);
  for (int i = 0; i < fontFace->ftFace->num_charmaps; i++) {
    v8::Handle<v8::Object> charmap = v8::Object::New(isolate);
    charmap->Set(v8::String::NewFromUtf8(isolate, "encoding"), v8::Integer::New(isolate, fontFace->ftFace->charmaps[i]->encoding));
    charmap->Set(v8::String::NewFromUtf8(isolate, "platform_id"), v8::Integer::New(isolate, fontFace->ftFace->charmaps[i]->platform_id));
    charmap->Set(v8::String::NewFromUtf8(isolate, "encoding_id"), v8::Integer::New(isolate, fontFace->ftFace->charmaps[i]->encoding_id));
    charmaps->Set(i, charmap);
  }
  info.GetReturnValue().Set(charmaps);
}

void FontFace::acc_bbox(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Handle<v8::Object> bbox = v8::Object::New(isolate);
  bbox->Set(v8::String::NewFromUtf8(isolate, "xMin"), v8::Integer::New(isolate, fontFace->ftFace->bbox.xMin));
  bbox->Set(v8::String::NewFromUtf8(isolate, "xMax"), v8::Integer::New(isolate, fontFace->ftFace->bbox.xMax));
  bbox->Set(v8::String::NewFromUtf8(isolate, "yMin"), v8::Integer::New(isolate, fontFace->ftFace->bbox.yMin));
  bbox->Set(v8::String::NewFromUtf8(isolate, "yMax"), v8::Integer::New(isolate, fontFace->ftFace->bbox.yMax));
  info.GetReturnValue().Set(bbox);
}

void FontFace::acc_units_per_EM(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->units_per_EM));
}

void FontFace::acc_ascender(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->ascender));
}

void FontFace::acc_descender(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->descender));
}

void FontFace::acc_height(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->height));
}

void FontFace::acc_max_advance_width(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->max_advance_width));
}

void FontFace::acc_max_advance_height(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->max_advance_height));
}

void FontFace::acc_underline_position(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->underline_position));
}

void FontFace::acc_underline_thickness(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(v8::Integer::New(v8::Isolate::GetCurrent(), fontFace->ftFace->underline_thickness));
}

void FontFace::acc_glyph(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info) {
  v8::Isolate* isolate = v8::Isolate::GetCurrent();

  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());

  v8::Local<v8::Object> glyphSlotWrapper = v8::Local<v8::Function>::New(isolate, GlyphSlot::constructor)->NewInstance();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(glyphSlotWrapper);
  glyphSlot->ftGlyphSlot = fontFace->ftFace->glyph;

  info.GetReturnValue().Set(glyphSlotWrapper);
}
