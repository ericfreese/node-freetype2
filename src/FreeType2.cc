#include "util.h"
#include "FontFace.h"
#include "enums.h"

Napi::Value NewMemoryFace(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  auto instanceData = env.GetInstanceData<InstanceData>();
  if (instanceData == nullptr) {
    Napi::TypeError::New(env, "Thread is not initialised!").ThrowAsJavaScriptException();
    return env.Null();
  }

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
      instanceData->library,
      buffer.Data(),
      buffer.Length(),
      faceIndex,
      &ftFace);

  if (err != 0)
  {
    throwJsException(env, err);
    return env.Null();
  }

  Napi::Object fontFace = instanceData->fontFace.New({});
  FontFace* fontFaceInner = FontFace::Unwrap(fontFace);
  fontFaceInner->ftFace = ftFace;
  fontFaceInner->bufferRef = Napi::Reference<Napi::Buffer<FT_Byte>>::New(buffer, 1);

  return fontFace;
}

Napi::Value NewFace(const Napi::CallbackInfo &info)
{
  Napi::Env env = info.Env();

  auto instanceData = env.GetInstanceData<InstanceData>();
  if (instanceData == nullptr) {
    Napi::TypeError::New(env, "Thread is not initialised!").ThrowAsJavaScriptException();
    return env.Null();
  }

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
      instanceData->library,
      filepath.c_str(),
      faceIndex,
      &ftFace);

  if (err != 0)
  {
    throwJsException(env, err);
    return env.Null();
  }

  Napi::Object fontFace = instanceData->fontFace.New({});
  FontFace* fontFaceInner = FontFace::Unwrap(fontFace);
  fontFaceInner->ftFace = ftFace;

  return fontFace;
}

void CleanupInstanceData(Napi::Env env, InstanceData* instanceData) {
  if (instanceData) {
    FT_Done_FreeType(instanceData->library);
    delete instanceData;
  }
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
  auto instanceData = new InstanceData{};

  FT_Init_FreeType(&instanceData->library);

  char version[32];
  sprintf(version, "%i.%i.%i", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
  exports.Set("FreeTypeVersion", version);

  exports.Set("NewFace", Napi::Function::New(env, NewFace));
  exports.Set("NewMemoryFace", Napi::Function::New(env, NewMemoryFace));

  instanceData->fontFace = FontFace::Initialize(env);
  InitializeEnums(env, exports);

  // Store the constructor as the add-on instance data
  env.SetInstanceData<InstanceData, CleanupInstanceData>(instanceData);

  return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)
