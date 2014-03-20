#include "FontFace.h"

void FontFace::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  v8::Local<v8::FunctionTemplate> constructorTemplate = v8::FunctionTemplate::New(New);
  constructorTemplate->SetClassName(NanSymbol("FontFace"));

  v8::Local<v8::ObjectTemplate> constructorObjectTemplate = constructorTemplate->InstanceTemplate();
  constructorObjectTemplate->SetAccessor(NanSymbol("num_faces"), acc_num_faces);
  constructorObjectTemplate->SetAccessor(NanSymbol("face_index"), acc_face_index);
  constructorObjectTemplate->SetAccessor(NanSymbol("face_flags"), acc_face_flags);
  constructorObjectTemplate->SetAccessor(NanSymbol("style_flags"), acc_style_flags);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_glyphs"), acc_num_glyphs);
  constructorObjectTemplate->SetAccessor(NanSymbol("family_name"), acc_family_name);
  constructorObjectTemplate->SetAccessor(NanSymbol("style_name"), acc_style_name);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_fixed_sizes"), acc_num_fixed_sizes);
  constructorObjectTemplate->SetAccessor(NanSymbol("available_sizes"), acc_available_sizes);
  constructorObjectTemplate->SetAccessor(NanSymbol("num_charmaps"), acc_num_charmaps);
  constructorObjectTemplate->SetAccessor(NanSymbol("charmaps"), acc_charmaps);
  constructorObjectTemplate->SetAccessor(NanSymbol("bbox"), acc_bbox);
  constructorObjectTemplate->SetAccessor(NanSymbol("units_per_EM"), acc_units_per_EM);
  constructorObjectTemplate->SetAccessor(NanSymbol("ascender"), acc_ascender);
  constructorObjectTemplate->SetAccessor(NanSymbol("descender"), acc_descender);
  constructorObjectTemplate->SetAccessor(NanSymbol("height"), acc_height);
  constructorObjectTemplate->SetAccessor(NanSymbol("max_advance_width"), acc_max_advance_width);
  constructorObjectTemplate->SetAccessor(NanSymbol("max_advance_height"), acc_max_advance_height);
  constructorObjectTemplate->SetAccessor(NanSymbol("underline_position"), acc_underline_position);
  constructorObjectTemplate->SetAccessor(NanSymbol("underline_thickness"), acc_underline_thickness);
  constructorObjectTemplate->SetAccessor(NanSymbol("glyph"), acc_glyph);
  // constructorObjectTemplate->SetAccessor(NanSymbol("size"), acc_size);
  // constructorObjectTemplate->SetAccessor(NanSymbol("charmap"), acc_charmap);
  constructorObjectTemplate->SetInternalFieldCount(1);

  NanAssignPersistent(v8::Function, constructor, constructorTemplate->GetFunction());
}

v8::Persistent<v8::Function> FontFace::constructor;

NAN_METHOD(FontFace::New) {
  NanScope();
  FontFace* fontFace = new FontFace();
  fontFace->Wrap(args.This());
  NanReturnValue(args.This());
}

FontFace::FontFace() {}

FontFace::~FontFace() {
  FT_Done_Face(this->ftFace);
}

NAN_GETTER(FontFace::acc_num_faces) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->num_faces));
}

NAN_GETTER(FontFace::acc_face_index) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->face_index));
}

NAN_GETTER(FontFace::acc_face_flags) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->face_flags));
}

NAN_GETTER(FontFace::acc_style_flags) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->style_flags));
}

NAN_GETTER(FontFace::acc_num_glyphs) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->num_glyphs));
}

NAN_GETTER(FontFace::acc_family_name) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::String::New(fontFace->ftFace->family_name));
}

NAN_GETTER(FontFace::acc_style_name) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::String::New(fontFace->ftFace->style_name));
}

NAN_GETTER(FontFace::acc_num_fixed_sizes) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->num_fixed_sizes));
}

NAN_GETTER(FontFace::acc_available_sizes) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Array> available_sizes = v8::Array::New(fontFace->ftFace->num_fixed_sizes);
  for (int i = 0; i < fontFace->ftFace->num_fixed_sizes; i++) {
    v8::Handle<v8::Object> size = v8::Object::New();
    size->Set(NanSymbol("height"), v8::Integer::New(fontFace->ftFace->available_sizes[i].height));
    size->Set(NanSymbol("width"), v8::Integer::New(fontFace->ftFace->available_sizes[i].width));
    size->Set(NanSymbol("size"), v8::Number::New(fontFace->ftFace->available_sizes[i].size));
    size->Set(NanSymbol("x_ppem"), v8::Number::New(fontFace->ftFace->available_sizes[i].x_ppem));
    size->Set(NanSymbol("y_ppem"), v8::Number::New(fontFace->ftFace->available_sizes[i].y_ppem));
    available_sizes->Set(i, size);
  }
  NanReturnValue(available_sizes);
}

NAN_GETTER(FontFace::acc_num_charmaps) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->num_charmaps));
}

NAN_GETTER(FontFace::acc_charmaps) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Array> charmaps = v8::Array::New(fontFace->ftFace->num_charmaps);
  for (int i = 0; i < fontFace->ftFace->num_charmaps; i++) {
    v8::Handle<v8::Object> charmap = v8::Object::New();
    charmap->Set(NanSymbol("encoding"), v8::Integer::New(fontFace->ftFace->charmaps[i]->encoding));
    charmap->Set(NanSymbol("platform_id"), v8::Integer::New(fontFace->ftFace->charmaps[i]->platform_id));
    charmap->Set(NanSymbol("encoding_id"), v8::Integer::New(fontFace->ftFace->charmaps[i]->encoding_id));
    charmaps->Set(i, charmap);
  }
  NanReturnValue(charmaps);
}

NAN_GETTER(FontFace::acc_bbox) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Object> bbox = v8::Object::New();
  bbox->Set(NanSymbol("xMin"), v8::Integer::New(fontFace->ftFace->bbox.xMin));
  bbox->Set(NanSymbol("xMax"), v8::Integer::New(fontFace->ftFace->bbox.xMax));
  bbox->Set(NanSymbol("yMin"), v8::Integer::New(fontFace->ftFace->bbox.yMin));
  bbox->Set(NanSymbol("yMax"), v8::Integer::New(fontFace->ftFace->bbox.yMax));
  NanReturnValue(bbox);
}

NAN_GETTER(FontFace::acc_units_per_EM) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->units_per_EM));
}

NAN_GETTER(FontFace::acc_ascender) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->ascender));
}

NAN_GETTER(FontFace::acc_descender) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->descender));
}

NAN_GETTER(FontFace::acc_height) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->height));
}

NAN_GETTER(FontFace::acc_max_advance_width) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->max_advance_width));
}

NAN_GETTER(FontFace::acc_max_advance_height) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->max_advance_height));
}

NAN_GETTER(FontFace::acc_underline_position) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->underline_position));
}

NAN_GETTER(FontFace::acc_underline_thickness) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  NanReturnValue(v8::Integer::New(fontFace->ftFace->underline_thickness));
}

NAN_GETTER(FontFace::acc_glyph) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(args.This());
  v8::Handle<v8::Object> glyphObj = Glyph::constructor->NewInstance();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(glyphObj);
  glyph->ftGlyph = fontFace->ftFace->glyph;
  NanReturnValue(glyphObj);
}
