#include "util.h"

void throwJsException(Napi::Env env, int errorCode) {
    const char *errString = FT_Error_String(errorCode);
    // TODO - errString could be null
    if (errString != nullptr)
    {
      Napi::TypeError::New(env, errString).ThrowAsJavaScriptException();
    } else {
      Napi::TypeError::New(env, "An unknown error occured").ThrowAsJavaScriptException();
    }
}
