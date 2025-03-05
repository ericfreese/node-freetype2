#include "FontFace.h"
#include <iostream>

/**
 * Unimplemented:
 * FT_Face_Properties
 */

Napi::FunctionReference
FontFace::Initialize(Napi::Env& env) {
  Napi::HandleScope scope(env);

  Napi::Function ctor = DefineClass(env, "FontFace", {
    InstanceMethod("properties", &FontFace::GetProperties),

    InstanceMethod("setCharSize", &FontFace::SetCharSize),
    InstanceMethod("setPixelSizes", &FontFace::SetPixelSizes),
    // InstanceMethod("requestSize", &FontFace::RequestSize),
    InstanceMethod("selectSize", &FontFace::SelectSize),
    InstanceMethod("setTransform", &FontFace::SetTransform),
    InstanceMethod("loadGlyph", &FontFace::LoadGlyph),
    InstanceMethod("getCharIndex", &FontFace::GetCharIndex),
    InstanceMethod("getFirstChar", &FontFace::GetFirstChar),
    InstanceMethod("getNextChar", &FontFace::GetNextChar),
    // InstanceMethod("getNameIndex", &FontFace::GetGetNameIndex),
    InstanceMethod("loadChar", &FontFace::LoadChar),
    InstanceMethod("renderGlyph", &FontFace::RenderGlyph),
    InstanceMethod("getKerning", &FontFace::GetKerning),
    // InstanceMethod("getTrackKerning", &FontFace::GetTrackKerning),
    // InstanceMethod("getGlyphName", &FontFace::GetGlyphName),
    // InstanceMethod("getPostscriptName", &FontFace::GetPostscriptName),
    // InstanceMethod("selectCharmap", &FontFace::SelectCharmap),
    // InstanceMethod("setCharmap", &FontFace::SetCharmap),
    // InstanceMethod("getCharmapIndex", &FontFace::GetCharmapIndex),
    // InstanceMethod("getFSTypeFlags", &FontFace::GetFSTypeFlags),
    // InstanceMethod("getSubGlyphInfo", &FontFace::GetSubGlyphInfo),

  });

  return Napi::Persistent(ctor);
}

FontFace::FontFace(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<FontFace>(info) {
}

FontFace::~FontFace() {
  FT_Done_Face(ftFace);
  if (!bufferRef.IsEmpty())
    bufferRef.Unref();
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
    availableSizes[(uint32_t) i] = size;
  }
  obj.Set("availableSizes", availableSizes);

//     FT_Int            num_charmaps;
//     FT_CharMap*       charmaps;

  Napi::Object bbox = Napi::Object::New(env);
  bbox.Set("xMin", this->ftFace->bbox.xMin);
  bbox.Set("yMin", this->ftFace->bbox.yMin);
  bbox.Set("xMax", this->ftFace->bbox.xMax);
  bbox.Set("yMax", this->ftFace->bbox.yMax);
  obj.Set("bbox", bbox);

  obj.Set("unitsPerEM", this->ftFace->units_per_EM);
  obj.Set("ascender", this->ftFace->ascender);
  obj.Set("descender", this->ftFace->descender);
  obj.Set("height", this->ftFace->height);

  obj.Set("maxAdvanceWidth", this->ftFace->max_advance_width);
  obj.Set("maxAdvanceHeight", this->ftFace->max_advance_height);

  obj.Set("underlinePosition", this->ftFace->underline_position);
  obj.Set("underlineThickness", this->ftFace->underline_thickness);

  Napi::Object size = Napi::Object::New(env);
  size.Set("xppem", this->ftFace->size->metrics.x_ppem);
  size.Set("yppem", this->ftFace->size->metrics.y_ppem);
  size.Set("xScale", this->ftFace->size->metrics.x_scale);
  size.Set("yScale", this->ftFace->size->metrics.y_scale);
  size.Set("ascender", this->ftFace->size->metrics.ascender);
  size.Set("descender", this->ftFace->size->metrics.descender);
  size.Set("height", this->ftFace->size->metrics.height);
  size.Set("maxAdvance", this->ftFace->size->metrics.max_advance);
  obj.Set("size", size);

    // FT_CharMap        charmap;

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

  FT_F26Dot6 charWidth = info[0].As<Napi::Number>().Int32Value() << 6; // TODO - handle float values
  FT_F26Dot6 charHeight = info[1].As<Napi::Number>().Int32Value() << 6; // TODO - handle float values
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

// Napi::Value FontFace::RequestSize(const Napi::CallbackInfo &info) {
//   Napi::Env env = info.Env();

//   if (
//     !validatePropsLength(env, info, 1) ||
//     !validateProp(env, info[0].IsObject(), "props")
//   ) {
//     return env.Null();
//   }

//   Napi::Object props = info[0].As<Napi::Object>();

//   Napi::Value rawType = props.Get("type");
//   Napi::Value rawWidth = props.Get("width");
//   Napi::Value rawHeight = props.Get("height");
//   Napi::Value rawHoriRes = props.Get("horiResolution");
//   Napi::Value rawVertRes = props.Get("vertResolution");

//   if (
//     !validateProp(env, rawType.IsNumber(), "type") ||
//     !validateProp(env, rawWidth.IsNumber(), "width") ||
//     !validateProp(env, rawHeight.IsNumber(), "height") ||
//     !validateProp(env, rawHoriRes.IsNumber(), "horiResolution") ||
//     !validateProp(env, rawVertRes.IsNumber(), "vertResolution")
//   ) {
//     return env.Null();
//   }

//   auto type = rawType.As<Napi::Number>().Int32Value();
//   if (type < 0 || type > FT_SIZE_REQUEST_TYPE_MAX) {
//     Napi::TypeError::New(env, "Invalid type").ThrowAsJavaScriptException();
//     return env.Null();
//   }

//   FT_Size_RequestRec req = {
//     static_cast<FT_Size_Request_Type>(type),
//     static_cast<FT_Long>(rawWidth.As<Napi::Number>().Int32Value()),
//     static_cast<FT_Long>(rawHeight.As<Napi::Number>().Int32Value()),
//     static_cast<FT_UInt>(rawHoriRes.As<Napi::Number>().Int32Value()),
//     static_cast<FT_UInt>(rawVertRes.As<Napi::Number>().Int32Value())
//   };

//   FT_Error err = FT_Request_Size(this->ftFace, &req);
//   if (err != 0) {
//     throwJsException(env, err);
//     return env.Null();
//   }

//   return env.Undefined();
// }

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
  FT_Matrix* matrixPtr = nullptr;
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
  FT_Vector* deltaPtr = nullptr;
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
    loadFlags |= FT_LOAD_NO_SCALE;
  if (checkProperty(rawFlags, "noHinting")) 
    loadFlags |= FT_LOAD_NO_HINTING;
  if (checkProperty(rawFlags, "render")) 
    loadFlags |= FT_LOAD_RENDER;
  if (checkProperty(rawFlags, "noBitmap")) 
    loadFlags |= FT_LOAD_NO_BITMAP;
  if (checkProperty(rawFlags, "verticalLayout")) 
    loadFlags |= FT_LOAD_VERTICAL_LAYOUT;
  if (checkProperty(rawFlags, "forceAutohint")) 
    loadFlags |= FT_LOAD_FORCE_AUTOHINT;
  if (checkProperty(rawFlags, "pedantic")) 
    loadFlags |= FT_LOAD_PEDANTIC;
  if (checkProperty(rawFlags, "noRecurse")) 
    loadFlags |= FT_LOAD_NO_RECURSE;
  if (checkProperty(rawFlags, "ignoreTransform")) 
    loadFlags |= FT_LOAD_IGNORE_TRANSFORM;
  if (checkProperty(rawFlags, "monochrome")) 
    loadFlags |= FT_LOAD_MONOCHROME;
  if (checkProperty(rawFlags, "linearDesign")) 
    loadFlags |= FT_LOAD_LINEAR_DESIGN;
  if (checkProperty(rawFlags, "noAutohint")) 
    loadFlags |= FT_LOAD_NO_AUTOHINT;
  if (checkProperty(rawFlags, "color")) 
    loadFlags |= FT_LOAD_COLOR;
  if (checkProperty(rawFlags, "computeMetrics")) 
    loadFlags |= FT_LOAD_COMPUTE_METRICS;
  if (checkProperty(rawFlags, "bitmapMetricsOnly")) 
    loadFlags |= FT_LOAD_BITMAP_METRICS_ONLY;

  Napi::Value loadTarget = rawFlags.Get("loadTarget");
  if (loadTarget.IsNumber())
    loadFlags |= FT_LOAD_TARGET_(loadTarget.As<Napi::Number>().Int32Value());

  return loadFlags;
}

Napi::Object fetchGlyphBitmap(const Napi::Env &env, const FT_GlyphSlot &glyph) {
  Napi::Object obj = Napi::Object::New(env);

  if (glyph->bitmap.buffer != nullptr) {
    Napi::Object bitmap = Napi::Object::New(env);
    bitmap.Set("width", glyph->bitmap.width);
    bitmap.Set("height", glyph->bitmap.rows);
    bitmap.Set("pitch", glyph->bitmap.pitch);
    bitmap.Set("pixelMode", glyph->bitmap.pixel_mode);

    if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_GRAY) {
      bitmap.Set("numGrays", glyph->bitmap.num_grays);
    } else {
      bitmap.Set("numGrays", env.Null());
    }

    Napi::Buffer<unsigned char> buffer = Napi::Buffer<unsigned char>::Copy(env, glyph->bitmap.buffer, glyph->bitmap.pitch * glyph->bitmap.rows);
    bitmap.Set("buffer", buffer);

    obj.Set("bitmap", bitmap);
    obj.Set("bitmapLeft", glyph->bitmap_left);
    obj.Set("bitmapTop", glyph->bitmap_top);
  } else {
    obj.Set("bitmap", env.Null());
    obj.Set("bitmapLeft", env.Null());
    obj.Set("bitmapTop", env.Null());
  }

  return obj;
}

Napi::Object fetchGlyph(const Napi::Env &env, const FT_GlyphSlot &glyph, const FT_Int32 loadFlags) {
  Napi::Object obj = fetchGlyphBitmap(env, glyph);

  Napi::Object metrics = Napi::Object::New(env);
  bool noScale = (loadFlags & FT_LOAD_NO_SCALE) != 0;
  metrics.Set("isFontUnits", noScale);
  metrics.Set("width", glyph->metrics.width);
  metrics.Set("height", glyph->metrics.height);
  metrics.Set("horiBearingX", glyph->metrics.horiBearingX);
  metrics.Set("horiBearingY", glyph->metrics.horiBearingY);
  metrics.Set("horiAdvance", glyph->metrics.horiAdvance);
  metrics.Set("vertBearingX", glyph->metrics.vertBearingX);
  metrics.Set("vertBearingY", glyph->metrics.vertBearingY);
  metrics.Set("vertAdvance", glyph->metrics.vertAdvance);
  obj.Set("metrics", metrics);

  unsigned long formatNum = glyph->format;
  obj.Set("format", formatNum);

  obj.Set("lsbDelta", glyph->lsb_delta);
  obj.Set("rsbDelta", glyph->rsb_delta);

  return obj;
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

  if (info.Length() >= 2 && !info[1].IsUndefined()) {
    if (
      !validateProp(env, info[1].IsObject(), "loadFlags")
    ) {
      return env.Null();
    }

    // flags
    loadFlags = parseLoadFlags(info[1].As<Napi::Object>());
  }

  FT_Error err = FT_Load_Glyph(this->ftFace, glyphIndex, loadFlags);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return fetchGlyph(env, this->ftFace->glyph, loadFlags);
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

  if (glyphIndex == 0) {
    return env.Null();
  } else {
    Napi::Object res = Napi::Object::New(env);
    res.Set("charCode", charCode);
    res.Set("glyphIndex", glyphIndex);
    return res;
  }
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

  if (glyphIndex == 0) {
    return env.Null();
  } else {
    Napi::Object res = Napi::Object::New(env);
    res.Set("charCode", charCode);
    res.Set("glyphIndex", glyphIndex);
    return res;
  }
}

Napi::Value FontFace::RenderGlyph(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "renderMode")
  ) {
    return env.Null();
  }

  FT_Render_Mode renderMode = (FT_Render_Mode) info[0].As<Napi::Number>().Int32Value();
  if (renderMode < 0 || renderMode > FT_RENDER_MODE_MAX) {
    Napi::TypeError::New(env, "Invalid renderMode").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_Error err = FT_Render_Glyph(this->ftFace->glyph, renderMode);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return fetchGlyphBitmap(env, this->ftFace->glyph);
}

Napi::Value FontFace::LoadChar(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 1) ||
    !validateProp(env, info[0].IsNumber(), "charCode")
  ) {
    return env.Null();
  }

  FT_UInt charCode = info[0].As<Napi::Number>().Uint32Value();
  FT_Int32 loadFlags = 0;

  if (info.Length() >= 2 && !info[1].IsUndefined()) {
    if (
      !validateProp(env, info[1].IsObject(), "loadFlags")
    ) {
      return env.Null();
    }

    // flags
    loadFlags = parseLoadFlags(info[1].As<Napi::Object>());
  }

  FT_Error err = FT_Load_Char(this->ftFace, charCode, loadFlags);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  return fetchGlyph(env, this->ftFace->glyph, loadFlags);
}

Napi::Value FontFace::GetKerning(const Napi::CallbackInfo &info) {
  Napi::Env env = info.Env();

  if (
    !validatePropsLength(env, info, 3) ||
    !validateProp(env, info[0].IsNumber(), "leftGlyphIndex") ||
    !validateProp(env, info[1].IsNumber(), "rightGlyphIndex") ||
    !validateProp(env, info[2].IsNumber(), "kerningMode")
  ) {
    return env.Null();
  }

  FT_UInt leftGlyphIndex = info[0].As<Napi::Number>().Int32Value();
  FT_UInt rightGlyphIndex = info[1].As<Napi::Number>().Int32Value();

  FT_UInt kerningMode = info[2].As<Napi::Number>().Uint32Value();
  if (kerningMode > FT_KERNING_UNSCALED) {
    Napi::TypeError::New(env, "Invalid kerningMode").ThrowAsJavaScriptException();
    return env.Null();
  }

  FT_Vector akerning;
  FT_Error err = FT_Get_Kerning(this->ftFace, leftGlyphIndex, rightGlyphIndex, kerningMode, &akerning);
  if (err != 0) {
    throwJsException(env, err);
    return env.Null();
  }

  Napi::Object res = Napi::Object::New(env);
  res.Set("x", akerning.x);
  res.Set("y", akerning.y);
  return res;
}

// Napi::Value FontFace::GetTrackKerning(const Napi::CallbackInfo &info) {
//   Napi::Env env = info.Env();

//   if (
//     !validatePropsLength(env, info, 2) ||
//     !validateProp(env, info[0].IsNumber(), "pointSize") ||
//     !validateProp(env, info[1].IsNumber(), "degree")
//   ) {
//     return env.Null();
//   }

//   FT_Fixed pointSize = info[0].As<Napi::Number>().Int32Value();
//   FT_Int degree = info[1].As<Napi::Number>().Int32Value();

//   FT_Fixed akerning;
//   FT_Error err = FT_Get_Track_Kerning(this->ftFace, pointSize, degree, &akerning);
//   if (err != 0) {
//     throwJsException(env, err);
//     return env.Null();
//   }

//   return Napi::Number::New(env, akerning);
// }
