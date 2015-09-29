#include "FontFace.h"

Nan::Persistent<v8::Function> FontFace::constructor;

v8::Local<v8::FunctionTemplate> FontFace::CreateConstructorTemplate() {
  Nan::EscapableHandleScope scope;

  v8::Local<v8::FunctionTemplate> constructorTemplate = Nan::New<v8::FunctionTemplate>(New);
  constructorTemplate->SetClassName(Nan::New("FontFace").ToLocalChecked());

  v8::Local<v8::ObjectTemplate> instanceTemplate = constructorTemplate->InstanceTemplate();
  Nan::SetAccessor(instanceTemplate, Nan::New("num_faces").ToLocalChecked(), acc_num_faces);
  Nan::SetAccessor(instanceTemplate, Nan::New("face_index").ToLocalChecked(), acc_face_index);
  Nan::SetAccessor(instanceTemplate, Nan::New("face_flags").ToLocalChecked(), acc_face_flags);
  Nan::SetAccessor(instanceTemplate, Nan::New("style_flags").ToLocalChecked(), acc_style_flags);
  Nan::SetAccessor(instanceTemplate, Nan::New("num_glyphs").ToLocalChecked(), acc_num_glyphs);
  Nan::SetAccessor(instanceTemplate, Nan::New("family_name").ToLocalChecked(), acc_family_name);
  Nan::SetAccessor(instanceTemplate, Nan::New("style_name").ToLocalChecked(), acc_style_name);
  Nan::SetAccessor(instanceTemplate, Nan::New("available_sizes").ToLocalChecked(), acc_available_sizes);
  Nan::SetAccessor(instanceTemplate, Nan::New("charmaps").ToLocalChecked(), acc_charmaps);
  Nan::SetAccessor(instanceTemplate, Nan::New("bbox").ToLocalChecked(), acc_bbox);
  Nan::SetAccessor(instanceTemplate, Nan::New("units_per_EM").ToLocalChecked(), acc_units_per_EM);
  Nan::SetAccessor(instanceTemplate, Nan::New("ascender").ToLocalChecked(), acc_ascender);
  Nan::SetAccessor(instanceTemplate, Nan::New("descender").ToLocalChecked(), acc_descender);
  Nan::SetAccessor(instanceTemplate, Nan::New("height").ToLocalChecked(), acc_height);
  Nan::SetAccessor(instanceTemplate, Nan::New("max_advance_width").ToLocalChecked(), acc_max_advance_width);
  Nan::SetAccessor(instanceTemplate, Nan::New("max_advance_height").ToLocalChecked(), acc_max_advance_height);
  Nan::SetAccessor(instanceTemplate, Nan::New("underline_position").ToLocalChecked(), acc_underline_position);
  Nan::SetAccessor(instanceTemplate, Nan::New("underline_thickness").ToLocalChecked(), acc_underline_thickness);
  Nan::SetAccessor(instanceTemplate, Nan::New("glyph").ToLocalChecked(), acc_glyph);
  instanceTemplate->SetInternalFieldCount(1);

  return scope.Escape(constructorTemplate);
}

v8::Local<v8::Function> FontFace::GetConstructor() {
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

NAN_METHOD(FontFace::New) {
  FontFace* fontFace = new FontFace();
  fontFace->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

FontFace::FontFace() {}

FontFace::~FontFace() {
  FT_Done_Face(this->ftFace);
}

NAN_GETTER(FontFace::acc_num_faces) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->num_faces));
}

NAN_GETTER(FontFace::acc_face_index) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->face_index));
}

NAN_GETTER(FontFace::acc_face_flags) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->face_flags));
}

NAN_GETTER(FontFace::acc_style_flags) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->style_flags));
}

NAN_GETTER(FontFace::acc_num_glyphs) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->num_glyphs));
}

NAN_GETTER(FontFace::acc_family_name) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New(fontFace->ftFace->family_name).ToLocalChecked());
}

NAN_GETTER(FontFace::acc_style_name) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New(fontFace->ftFace->style_name).ToLocalChecked());
}

NAN_GETTER(FontFace::acc_available_sizes) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Local<v8::Array> available_sizes = Nan::New<v8::Array>(fontFace->ftFace->num_fixed_sizes);

  for (int i = 0; i < fontFace->ftFace->num_fixed_sizes; i++) {
    v8::Local<v8::Object> size = Nan::New<v8::Object>();
    size->Set(Nan::New("height").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->available_sizes[i].height));
    size->Set(Nan::New("width").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->available_sizes[i].width));
    size->Set(Nan::New("size").ToLocalChecked(), Nan::New((double)fontFace->ftFace->available_sizes[i].size));
    size->Set(Nan::New("x_ppem").ToLocalChecked(), Nan::New((double)fontFace->ftFace->available_sizes[i].x_ppem));
    size->Set(Nan::New("y_ppem").ToLocalChecked(), Nan::New((double)fontFace->ftFace->available_sizes[i].y_ppem));
    available_sizes->Set(i, size);
  }

  info.GetReturnValue().Set(available_sizes);
}

NAN_GETTER(FontFace::acc_charmaps) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Local<v8::Array> charmaps = Nan::New<v8::Array>(fontFace->ftFace->num_charmaps);

  for (int i = 0; i < fontFace->ftFace->num_charmaps; i++) {
    v8::Local<v8::Object> charmap = Nan::New<v8::Object>();
    charmap->Set(Nan::New("encoding").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->charmaps[i]->encoding));
    charmap->Set(Nan::New("platform_id").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->charmaps[i]->platform_id));
    charmap->Set(Nan::New("encoding_id").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->charmaps[i]->encoding_id));
    charmaps->Set(i, charmap);
  }

  info.GetReturnValue().Set(charmaps);
}

NAN_GETTER(FontFace::acc_bbox) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  v8::Local<v8::Object> bbox = Nan::New<v8::Object>();
  bbox->Set(Nan::New("xMin").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->bbox.xMin));
  bbox->Set(Nan::New("xMax").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->bbox.xMax));
  bbox->Set(Nan::New("yMin").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->bbox.yMin));
  bbox->Set(Nan::New("yMax").ToLocalChecked(), Nan::New((int32_t)fontFace->ftFace->bbox.yMax));
  info.GetReturnValue().Set(bbox);
}

NAN_GETTER(FontFace::acc_units_per_EM) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->units_per_EM));
}

NAN_GETTER(FontFace::acc_ascender) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->ascender));
}

NAN_GETTER(FontFace::acc_descender) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->descender));
}

NAN_GETTER(FontFace::acc_height) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->height));
}

NAN_GETTER(FontFace::acc_max_advance_width) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->max_advance_width));
}

NAN_GETTER(FontFace::acc_max_advance_height) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->max_advance_height));
}

NAN_GETTER(FontFace::acc_underline_position) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->underline_position));
}

NAN_GETTER(FontFace::acc_underline_thickness) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());
  info.GetReturnValue().Set(Nan::New((int32_t)fontFace->ftFace->underline_thickness));
}

NAN_GETTER(FontFace::acc_glyph) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(info.This());

  v8::Local<v8::Object> glyphSlotWrapper = Nan::NewInstance(GlyphSlot::GetConstructor()).ToLocalChecked();
  GlyphSlot* glyphSlot = node::ObjectWrap::Unwrap<GlyphSlot>(glyphSlotWrapper);
  glyphSlot->ftGlyphSlot = fontFace->ftFace->glyph;

  info.GetReturnValue().Set(glyphSlotWrapper);
}
