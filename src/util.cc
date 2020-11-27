#include "util.h"

void throwJsException(const Napi::Env& env, FT_Error errorCode) {
    const char *errString = FT_Error_String(errorCode);
    if (errString != nullptr)
    {
      Napi::TypeError::New(env, errString).ThrowAsJavaScriptException();
    } else {
      Napi::TypeError::New(env, "An unknown error occured").ThrowAsJavaScriptException();
    }
}

bool validateProp(const Napi::Env& env, bool isCorrect, const char* propName) {
  if (!isCorrect) {
    char str[255];
    sprintf(str, "%s is not valid", propName);

    Napi::TypeError::New(env, str).ThrowAsJavaScriptException();
  }

  return isCorrect;
}

bool validatePropsLength(const Napi::Env& env, const Napi::CallbackInfo &info, unsigned int minLength) {
  if (info.Length() < minLength) {
    Napi::TypeError::New(env, "Not enough arguments").ThrowAsJavaScriptException();
    return false;
  }
  return true;
}

bool checkProperty(const Napi::Object& obj, const char* name) {
  Napi::Value val = obj.Get(name);
  if (val.IsBoolean()) {
    return val.As<Napi::Boolean>().Value();
  } else if (val.IsNumber()) {
    return val.As<Napi::Number>().Int32Value() != 0;
  }

  return false;
}
