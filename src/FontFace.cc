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
    InstanceMethod("properties", &FontFace::GetProperties),

    InstanceMethod("setCharSize", &FontFace::SetCharSize),
    InstanceMethod("setPixelSizes", &FontFace::SetPixelSizes),
    InstanceMethod("requestSize", &FontFace::RequestSize),
    InstanceMethod("selectSize", &FontFace::SelectSize),
    InstanceMethod("setTransform", &FontFace::SetTransform),
    InstanceMethod("loadGlyph", &FontFace::LoadGlyph),
    InstanceMethod("getCharIndex", &FontFace::GetCharIndex),
    InstanceMethod("getFirstChar", &FontFace::GetFirstChar),
    InstanceMethod("getNextChar", &FontFace::GetNextChar),
    // TODO FT_Get_Name_Index
    InstanceMethod("loadChar", &FontFace::LoadChar),

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

bool hasFlag(FT_Long value, FT_Long flag) {
  return (value & flag) > 0;
}

Napi::Value FontFace::GetProperties(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  Napi::Object obj = Napi::Object::New(env);

  obj.Set("numFaces", this->ftFace->num_faces);
  obj.Set("faceIndex", this->ftFace->face_index);

  Napi::Object faceFlags = Napi::Object::New(env);
  faceFlags.Set("scalable", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_SCALABLE));
  faceFlags.Set("fixedSizes", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_FIXED_SIZES));
  faceFlags.Set("fixedWidth", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_FIXED_WIDTH));
  faceFlags.Set("sfnt", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_SFNT));
  faceFlags.Set("horizontal", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_HORIZONTAL));
  faceFlags.Set("vertical", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_VERTICAL));
  faceFlags.Set("kerning", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_KERNING));
  // faceFlags.Set("fastGlyphs", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_FAST_GLYPHS)); Flag is deprecated
  faceFlags.Set("multipleMasters", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_MULTIPLE_MASTERS));
  faceFlags.Set("glyphNames", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_GLYPH_NAMES));
  faceFlags.Set("externalStream", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_EXTERNAL_STREAM));
  faceFlags.Set("hinter", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_HINTER));
  faceFlags.Set("cidKeyed", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_CID_KEYED));
  faceFlags.Set("tricky", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_TRICKY));
  faceFlags.Set("color", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_COLOR));
  faceFlags.Set("variation", hasFlag(this->ftFace->face_flags, FT_FACE_FLAG_VARIATION));
  obj.Set("faceFlags", faceFlags);

  Napi::Object styleFlags = Napi::Object::New(env);
  styleFlags.Set("italic", hasFlag(this->ftFace->style_flags, FT_STYLE_FLAG_ITALIC));
  styleFlags.Set("bold", hasFlag(this->ftFace->style_flags, FT_STYLE_FLAG_BOLD));
  obj.Set("styleFlags", styleFlags);

  obj.Set("numGlyphs", this->ftFace->num_glyphs);
  obj.Set("familyName", this->ftFace->family_name);
  obj.Set("styleName", this->ftFace->style_name);

  Napi::Array availableSizes = Napi::Array::New(env, this->ftFace->num_fixed_sizes);
  for (FT_Int i = 0; i < this->ftFace->num_fixed_sizes; i++)
  {
    FT_Bitmap_Size* rawSize = &this->ftFace->available_sizes[i];
    Napi::Object size = Napi::Object::New(env);
    size.Set("height", rawSize->height);
    size.Set("width", rawSize->width);
    size.Set("size", rawSize->size);
    size.Set("xppem", rawSize->x_ppem);
    size.Set("yppem", rawSize->y_ppem);
    availableSizes[i] = size;
  }
  obj.Set("availableSizes", availableSizes);

//     FT_Int            num_charmaps;
//     FT_CharMap*       charmaps;

//     FT_Generic        generic;


  return obj;
}

Napi::Value FontFace::SetCharSize(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 4) ||
    !validateProp(env, info[0].IsNumber(), "charWidth") ||
    !validateProp(env, info[1].IsNumber(), "charHeight") ||
    !validateProp(env, info[2].IsNumber(), "horzResolution") ||
    !validateProp(env, info[3].IsNumber(), "vertResolution")
  ) {
    return env.Null();
  }

  FT_F26Dot6 charWidth = info[0].As<Napi::Number>().Int32Value(); // TODO - convert from a float?
  FT_F26Dot6 charHeight = info[1].As<Napi::Number>().Int32Value(); // TODO - convert from a float?
  FT_UInt horzResolution = info[2].As<Napi::Number>().Uint32Value();
  FT_UInt vertResolution = info[3].As<Napi::Number>().Uint32Value();

  FT_Error err = FT_Set_Char_Size(this->ftFace, charWidth, charHeight, horzResolution, vertResolution);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}

Napi::Value FontFace::SetPixelSizes(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 2) ||
    !validateProp(env, info[0].IsNumber(), "pixelWidth") ||
    !validateProp(env, info[1].IsNumber(), "pixelHeight")
  ) {
    return env.Null();
  }

  FT_UInt pixelWidth = info[0].As<Napi::Number>().Uint32Value();
  FT_UInt pixelHeight = info[1].As<Napi::Number>().Uint32Value();

  FT_Error err = FT_Set_Pixel_Sizes(this->ftFace, pixelWidth, pixelHeight);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}

Napi::Value FontFace::RequestSize(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsObject(), "props")
  ) {
    return env.Null();
  }

  Napi::Object props = info[0].As<Napi::Object>();

  Napi::Value rawType = props.Get("type");
  Napi::Value rawWidth = props.Get("width");
  Napi::Value rawHeight = props.Get("height");
  Napi::Value rawHoriRes = props.Get("horiResolution");
  Napi::Value rawVertRes = props.Get("vertResolution");

  if (
    !validateProp(env, rawType.IsNumber(), "type") ||
    !validateProp(env, rawWidth.IsNumber(), "width") ||
    !validateProp(env, rawHeight.IsNumber(), "height") ||
    !validateProp(env, rawHoriRes.IsNumber(), "horiResolution") ||
    !validateProp(env, rawVertRes.IsNumber(), "vertResolution")
  ) {
    return env.Null();
  }

  auto type = rawType.As<Napi::Number>().Int32Value();
  if (type < 0 || type > FT_SIZE_REQUEST_TYPE_MAX) {
    Napi::TypeError::New(env, "Invalid type").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_Size_RequestRec req = {
    static_cast<FT_Size_Request_Type>(type),
    static_cast<FT_Long>(rawWidth.As<Napi::Number>().Int32Value()),
    static_cast<FT_Long>(rawHeight.As<Napi::Number>().Int32Value()),
    static_cast<FT_UInt>(rawHoriRes.As<Napi::Number>().Int32Value()),
    static_cast<FT_UInt>(rawVertRes.As<Napi::Number>().Int32Value())
  };

  FT_Error err = FT_Request_Size(this->ftFace, &req);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}

Napi::Value FontFace::SelectSize(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "strikeIndex")
  ) {
    return env.Null();
  }

  FT_Error err = FT_Select_Size(this->ftFace, info[0].As<Napi::Number>().Int32Value());
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}

Napi::Value FontFace::SetTransform(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  Napi::Value rawMatrix = env.Undefined();
  Napi::Value rawDelta = env.Undefined();

  if (info.Length() >= 1) {
    rawMatrix = info[0];
  }
  if (info.Length() >= 2) {
    rawDelta = info[1];
  }

  if (
    !validateProp(env, rawMatrix.IsArray() || rawMatrix.IsUndefined(), "matrix") ||
    !validateProp(env, rawDelta.IsArray() || rawDelta.IsUndefined(), "delta")
  ) {
    return env.Null();
  }

  FT_Matrix matrix;
  FT_Matrix* matrixPtr;
  if (rawMatrix.IsArray()) {
    Napi::Array matrixArray = rawMatrix.As<Napi::Array>();
    if (matrixArray.Length() != 4) {
      Napi::TypeError::New(env, "Not enough matrix components").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (
      !validateProp(env, matrixArray.Get(0u).IsNumber(), "matrix.xx") ||
      !validateProp(env, matrixArray.Get(1u).IsNumber(), "matrix.xy") ||
      !validateProp(env, matrixArray.Get(2u).IsNumber(), "matrix.yx") ||
      !validateProp(env, matrixArray.Get(3u).IsNumber(), "matrix.yy")
    ) {
      return env.Null();
    }

    matrixPtr = &matrix;
    matrix.xx = matrixArray.Get(0u).As<Napi::Number>().Int32Value();
    matrix.xy = matrixArray.Get(1u).As<Napi::Number>().Int32Value();
    matrix.yx = matrixArray.Get(2u).As<Napi::Number>().Int32Value();
    matrix.yy = matrixArray.Get(3u).As<Napi::Number>().Int32Value();
  }

  FT_Vector delta;
  FT_Vector* deltaPtr;
  if (rawDelta.IsArray()) {
    Napi::Array deltaArray = rawDelta.As<Napi::Array>();
    if (deltaArray.Length() != 2) {
      Napi::TypeError::New(env, "Not enough delta components").ThrowAsJavaScriptException();
      return env.Null();
    }

    if (
      !validateProp(env, deltaArray.Get(0u).IsNumber(), "delta.x") ||
      !validateProp(env, deltaArray.Get(1u).IsNumber(), "delta.y")
    ) {
      return env.Null();
    }

    deltaPtr = &delta;
    delta.x = deltaArray.Get(0u).As<Napi::Number>().Int32Value();
    delta.y = deltaArray.Get(1u).As<Napi::Number>().Int32Value();
  }

  FT_Set_Transform(this->ftFace, matrixPtr, deltaPtr);

  return env.Undefined();
}

FT_Int32 parseLoadFlags(Napi::Object rawFlags) {
  FT_Int32 loadFlags = 0;

  if (checkProperty(rawFlags, "noScale")) 
    loadFlags &= FT_LOAD_NO_SCALE;
  if (checkProperty(rawFlags, "noHinting")) 
    loadFlags &= FT_LOAD_NO_HINTING;
  if (checkProperty(rawFlags, "render")) 
    loadFlags &= FT_LOAD_RENDER;
  if (checkProperty(rawFlags, "noBitmap")) 
    loadFlags &= FT_LOAD_NO_BITMAP;
  if (checkProperty(rawFlags, "verticalLayout")) 
    loadFlags &= FT_LOAD_VERTICAL_LAYOUT;
  if (checkProperty(rawFlags, "forceAutohint")) 
    loadFlags &= FT_LOAD_FORCE_AUTOHINT;
  if (checkProperty(rawFlags, "pedantic")) 
    loadFlags &= FT_LOAD_PEDANTIC;
  if (checkProperty(rawFlags, "noRecurse")) 
    loadFlags &= FT_LOAD_NO_RECURSE;
  if (checkProperty(rawFlags, "ignoreTransform")) 
    loadFlags &= FT_LOAD_IGNORE_TRANSFORM;
  if (checkProperty(rawFlags, "monochrome")) 
    loadFlags &= FT_LOAD_MONOCHROME;
  if (checkProperty(rawFlags, "linearDesign")) 
    loadFlags &= FT_LOAD_LINEAR_DESIGN;
  if (checkProperty(rawFlags, "noAutohint")) 
    loadFlags &= FT_LOAD_NO_AUTOHINT;
  if (checkProperty(rawFlags, "color")) 
    loadFlags &= FT_LOAD_COLOR;
  if (checkProperty(rawFlags, "computeMetrics")) 
    loadFlags &= FT_LOAD_COMPUTE_METRICS;
  if (checkProperty(rawFlags, "bitmapMetricsOnly")) 
    loadFlags &= FT_LOAD_BITMAP_METRICS_ONLY;

  return loadFlags;
}

Napi::Value FontFace::LoadGlyph(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "glyphIndex")
  ) {
    return env.Null();
  }

  FT_UInt glyphIndex = info[0].As<Napi::Number>().Int32Value();
  FT_Int32 loadFlags = 0;

  if (info.Length() >= 2) {
    if (
      !validateProp(env, info[2].IsObject(), "loadFlags")
    ) {
      return env.Null();
    }

    // flags
    loadFlags = parseLoadFlags(info[2].As<Napi::Object>());
  }

  FT_Error err = FT_Load_Glyph(this->ftFace, glyphIndex, loadFlags);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}

Napi::Value FontFace::GetCharIndex(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "charCode")
  ) {
    return env.Null();
  }

  FT_UInt index = FT_Get_Char_Index(this->ftFace, info[0].As<Napi::Number>().Uint32Value());
  if (index == 0) {
    return env.Null();
  } else {
    return Napi::Number::New(env, index);
  }
}

Napi::Value FontFace::GetFirstChar(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  FT_UInt glyphIndex;
  FT_ULong charCode = FT_Get_First_Char(this->ftFace, &glyphIndex);

  Napi::Object res = Napi::Object::New(env);
  res.Set("charCode", charCode);
  res.Set("glyphIndex", glyphIndex);
  return res;
}

Napi::Value FontFace::GetNextChar(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "charCode")
  ) {
    return env.Null();
  }

  FT_UInt afterCharCode = info[0].As<Napi::Number>().Uint32Value();

  FT_UInt glyphIndex;
  FT_ULong charCode = FT_Get_Next_Char(this->ftFace, afterCharCode, &glyphIndex);

  Napi::Object res = Napi::Object::New(env);
  res.Set("charCode", charCode);
  res.Set("glyphIndex", glyphIndex);
  return res;
}

Napi::Value FontFace::LoadChar(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "charCode")
  ) {
    return env.Null();
  }

  FT_UInt charCode = info[0].As<Napi::Number>().Int32Value();
  FT_Int32 loadFlags = 0;

  if (info.Length() >= 2) {
    if (
      !validateProp(env, info[2].IsObject(), "loadFlags")
    ) {
      return env.Null();
    }

    // flags
    loadFlags = parseLoadFlags(info[2].As<Napi::Object>());
  }

  FT_Error err = FT_Load_Char(this->ftFace, charCode, loadFlags);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return env.Undefined();
}
