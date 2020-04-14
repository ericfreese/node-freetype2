#include "util.h"
// #include "FreeType2.h"
#include "FontFace.h"

// TODO - when will this be freed?
FT_Library library;
char version[32];

Napi::String NewMemoryFace(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  return Napi::String::New(env, "world");
}

Napi::Value NewFace(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Not enough arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsString())
  {
    Napi::TypeError::New(env, "Invalid filepath").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_Long faceIndex = 0;
  if (info.Length() >= 2)
  {
    if (!info[1].IsNumber())
    {
      Napi::TypeError::New(env, "Invalid faceIndex").ThrowAsJavaScriptException();
      return env.Null();
    }
    faceIndex = info[1].As<Napi::Number>().Int32Value();
  }

  std::string filepath = info[0].As<Napi::String>().Utf8Value();

  FT_Face ftFace;
  FT_Error err = FT_New_Face(
      library,
      filepath.c_str(),
      faceIndex,
      &ftFace);

  if (err != 0)
  {
    throwJsException(env, err);
    return env.Null();
  }

  Napi::Object fontFace = FontFace::constructor.New({});
  FontFace* fontFaceInner = FontFace::Unwrap(fontFace);
  // TODO null guard?
  fontFaceInner->ftFace = ftFace;

  return fontFace;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  FT_Init_FreeType(&library);

  sprintf(version, "%i.%i.%i", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
  exports.Set("FreeTypeVersion", version);

  exports.Set("NewFace", Napi::Function::New(env, NewFace));
  exports.Set("NewMemoryFace", Napi::Function::New(env, NewMemoryFace));

  FontFace::Initialize(env);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
