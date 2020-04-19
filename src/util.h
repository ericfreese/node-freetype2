#define NAPI_VERSION 3
#include <napi.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void throwJsException(const Napi::Env& env, FT_Error errorCode);

bool validateProp(const Napi::Env& env, bool isCorrect, const char* propName);

bool validatePropsLength(const Napi::Env& env, const Napi::CallbackInfo &info, unsigned int minLength);

bool checkProperty(const Napi::Object& obj, const char* name);
