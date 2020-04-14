#include "FontFace.h"
#include <iostream>

Napi::FunctionReference FontFace::constructor;

/**
 * Unimplemented:
 * FT_Face_Properties
 */

void
FontFace::Initialize(Napi::Env& env) {
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "FontFace", {
    InstanceAccessor("numFaces", &FontFace::GetNumFaces, nullptr),
    InstanceAccessor("faceIndex", &FontFace::GetFaceIndex, nullptr),

    InstanceMethod("getCharIndex", &FontFace::GetCharIndex),
//     InstanceMethod("toBuffer", &Canvas::ToBuffer),
//     InstanceMethod("streamPNGSync", &Canvas::StreamPNGSync),
//     InstanceMethod("streamPDFSync", &Canvas::StreamPDFSync),
// #ifdef HAVE_JPEG
//     InstanceMethod("streamJPEGSync", &Canvas::StreamJPEGSync),
// #endif
//     InstanceAccessor("type", &Canvas::GetType, nullptr),
//     InstanceAccessor("stride", &Canvas::GetStride, nullptr),
//     InstanceAccessor("width", &Canvas::GetWidth, &Canvas::SetWidth),
//     InstanceAccessor("height", &Canvas::GetHeight, &Canvas::SetHeight),
//     InstanceValue("PNG_NO_FILTERS", Napi::Number::New(env, PNG_NO_FILTERS)),
//     InstanceValue("PNG_FILTER_NONE", Napi::Number::New(env, PNG_FILTER_NONE)),
//     InstanceValue("PNG_FILTER_SUB", Napi::Number::New(env, PNG_FILTER_SUB)),
//     InstanceValue("PNG_FILTER_UP", Napi::Number::New(env, PNG_FILTER_UP)),
//     InstanceValue("PNG_FILTER_AVG", Napi::Number::New(env, PNG_FILTER_AVG)),
//     InstanceValue("PNG_FILTER_PAETH", Napi::Number::New(env, PNG_FILTER_PAETH)),
//     InstanceValue("PNG_ALL_FILTERS", Napi::Number::New(env, PNG_ALL_FILTERS)),
//     StaticMethod("_registerFont", &Canvas::RegisterFont),
  });

  constructor = Napi::Persistent(ctor);
  constructor.SuppressDestruct();
  // target.Set("Canvas", ctor);
}

FontFace::FontFace(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<FontFace>(info) {
  // TODO
}

FontFace::~FontFace() {
  FT_Done_Face(ftFace);
}

Napi::Value FontFace::GetNumFaces(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), this->ftFace->num_faces);
}

Napi::Value FontFace::GetFaceIndex(const Napi::CallbackInfo &info) {
  return Napi::Number::New(info.Env(), this->ftFace->face_index);
}

Napi::Value FontFace::GetCharIndex(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (info.Length() < 1) {
    Napi::TypeError::New(env, "Missing charCode").ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsNumber()) {
    Napi::TypeError::New(env, "Invalid charCode").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_UInt index = FT_Get_Char_Index(this->ftFace, info[0].As<Napi::Number>().Uint32Value());
  if (index == 0) {
    return env.Null();
  } else {
    return Napi::Number::New(env, index);
  }
}