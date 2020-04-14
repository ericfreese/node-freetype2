#define NAPI_VERSION 3
#include <napi.h>

#include <ft2build.h>
#include FT_FREETYPE_H

void throwJsException(Napi::Env env, int errorCode);
