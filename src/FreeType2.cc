#include "util.h"
#include "FontFace.h"
#include "enums.h"

FT_Library library;
char version[32];

int z_verbose = 0;

void z_error (char* message)
{
}

Napi::Value NewMemoryFace(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  if (info.Length() < 1)
  {
    Napi::TypeError::New(env, "Not enough arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsBuffer())
  {
    Napi::TypeError::New(env, "Invalid buffer").ThrowAsJavaScriptException();
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

  Napi::Buffer<FT_Byte> buffer = info[0].As<Napi::Buffer<FT_Byte>>();

  if (buffer.Length() == 0)
  {
    Napi::TypeError::New(env, "Invalid buffer").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_Face ftFace;
  FT_Error err = FT_New_Memory_Face(
      library,
      buffer.Data(),
      buffer.Length(),
      faceIndex,
      &ftFace);

  if (err != 0)
  {
    throwJsException(env, err);
    return env.Null();
  }

  Napi::Object fontFace = FontFace::constructor.New({});
  FontFace* fontFaceInner = FontFace::Unwrap(fontFace);
  fontFaceInner->ftFace = ftFace;
  fontFaceInner->bufferRef = Napi::Reference<Napi::Buffer<FT_Byte>>::New(buffer, 1);

  return fontFace;
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
  InitializeEnums(env, exports);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
