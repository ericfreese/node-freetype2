#include "FreeType2.h"
#include "FontFace.h"

#define ARG_TO_INT32(value) Nan::To<int32_t>(value.As<v8::Number>()).ToChecked()
#define TO_INT32(value)     Nan::To<int32_t>(value).ToChecked()

FT_Library FreeType2::library;

NAN_MODULE_INIT(FreeType2::Init) {
  FT_Init_FreeType(&library);

  char version[32];
  sprintf(version, "%i.%i.%i", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
  Nan::Set(target, Nan::New("version").ToLocalChecked(), Nan::New(version).ToLocalChecked());

  Nan::SetMethod(target, "New_Memory_Face", New_Memory_Face);
  Nan::SetMethod(target, "Select_Size", Select_Size);
  Nan::SetMethod(target, "Request_Size", Request_Size);
  Nan::SetMethod(target, "Set_Char_Size", Set_Char_Size);
  Nan::SetMethod(target, "Set_Pixel_Sizes", Set_Pixel_Sizes);
  Nan::SetMethod(target, "Load_Glyph", Load_Glyph);
  Nan::SetMethod(target, "Load_Char", Load_Char);
  Nan::SetMethod(target, "Set_Transform", Set_Transform);
  Nan::SetMethod(target, "Render_Glyph", Render_Glyph);
  Nan::SetMethod(target, "Get_Kerning", Get_Kerning);
  // Nan::SetMethod(target, "Get_Track_Kerning", Get_Track_Kerning);
  // Nan::SetMethod(target, "Get_Glyph_Name", Get_Glyph_Name);
  // Nan::SetMethod(target, "Get_Postscript_Name", Get_Postscript_Name);
  Nan::SetMethod(target, "Select_Charmap", Select_Charmap);
  Nan::SetMethod(target, "Set_Charmap", Set_Charmap);
  Nan::SetMethod(target, "Get_Charmap_Index", Get_Charmap_Index);
  Nan::SetMethod(target, "Get_Char_Index", Get_Char_Index);
  Nan::SetMethod(target, "Get_First_Char", Get_First_Char);
  Nan::SetMethod(target, "Get_Next_Char", Get_Next_Char);
  // Nan::SetMethod(target, "Get_Name_Index", Get_Name_Index);
  // Nan::SetMethod(target, "Get_SubGlyph_Info", Get_SubGlyph_Info);

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Encoding
  Nan::Set(target, Nan::New("ENCODING_NONE").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_NONE));
  Nan::Set(target, Nan::New("ENCODING_MS_SYMBOL").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_MS_SYMBOL));
  Nan::Set(target, Nan::New("ENCODING_UNICODE").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_UNICODE));
  Nan::Set(target, Nan::New("ENCODING_SJIS").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_SJIS));
  Nan::Set(target, Nan::New("ENCODING_GB2312").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_GB2312));
  Nan::Set(target, Nan::New("ENCODING_BIG5").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_BIG5));
  Nan::Set(target, Nan::New("ENCODING_WANSUNG").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_WANSUNG));
  Nan::Set(target, Nan::New("ENCODING_JOHAB").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_JOHAB));
  Nan::Set(target, Nan::New("ENCODING_ADOBE_STANDARD").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_ADOBE_STANDARD));
  Nan::Set(target, Nan::New("ENCODING_ADOBE_EXPERT").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_ADOBE_EXPERT));
  Nan::Set(target, Nan::New("ENCODING_ADOBE_CUSTOM").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_ADOBE_CUSTOM));
  Nan::Set(target, Nan::New("ENCODING_ADOBE_LATIN_1").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_ADOBE_LATIN_1));
  Nan::Set(target, Nan::New("ENCODING_OLD_LATIN_2").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_OLD_LATIN_2));
  Nan::Set(target, Nan::New("ENCODING_APPLE_ROMAN").ToLocalChecked(), Nan::New((uint32_t)FT_ENCODING_APPLE_ROMAN));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_LOAD_XXX
  Nan::Set(target, Nan::New("LOAD_DEFAULT").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_DEFAULT));
  Nan::Set(target, Nan::New("LOAD_NO_SCALE").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_NO_SCALE));
  Nan::Set(target, Nan::New("LOAD_NO_HINTING").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_NO_HINTING));
  Nan::Set(target, Nan::New("LOAD_RENDER").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_RENDER));
  Nan::Set(target, Nan::New("LOAD_NO_BITMAP").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_NO_BITMAP));
  Nan::Set(target, Nan::New("LOAD_VERTICAL_LAYOUT").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_VERTICAL_LAYOUT));
  Nan::Set(target, Nan::New("LOAD_FORCE_AUTOHINT").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_FORCE_AUTOHINT));
  Nan::Set(target, Nan::New("LOAD_CROP_BITMAP").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_CROP_BITMAP));
  Nan::Set(target, Nan::New("LOAD_PEDANTIC").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_PEDANTIC));
  Nan::Set(target, Nan::New("LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH));
  Nan::Set(target, Nan::New("LOAD_NO_RECURSE").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_NO_RECURSE));
  Nan::Set(target, Nan::New("LOAD_IGNORE_TRANSFORM").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_IGNORE_TRANSFORM));
  Nan::Set(target, Nan::New("LOAD_MONOCHROME").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_MONOCHROME));
  Nan::Set(target, Nan::New("LOAD_LINEAR_DESIGN").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_LINEAR_DESIGN));
  Nan::Set(target, Nan::New("LOAD_NO_AUTOHINT").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_NO_AUTOHINT));
  Nan::Set(target, Nan::New("LOAD_COLOR").ToLocalChecked(), Nan::New((uint32_t)FT_LOAD_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Kerning_Mode
  Nan::Set(target, Nan::New("KERNING_DEFAULT").ToLocalChecked(), Nan::New((uint32_t)FT_KERNING_DEFAULT));
  Nan::Set(target, Nan::New("KERNING_UNFITTED").ToLocalChecked(), Nan::New((uint32_t)FT_KERNING_UNFITTED));
  Nan::Set(target, Nan::New("KERNING_UNSCALED").ToLocalChecked(), Nan::New((uint32_t)FT_KERNING_UNSCALED));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FACE_FLAG_XXX
  Nan::Set(target, Nan::New("FACE_FLAG_SCALABLE").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_SCALABLE));
  Nan::Set(target, Nan::New("FACE_FLAG_FIXED_SIZES").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_FIXED_SIZES));
  Nan::Set(target, Nan::New("FACE_FLAG_FIXED_WIDTH").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_FIXED_WIDTH));
  Nan::Set(target, Nan::New("FACE_FLAG_SFNT").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_SFNT));
  Nan::Set(target, Nan::New("FACE_FLAG_HORIZONTAL").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_HORIZONTAL));
  Nan::Set(target, Nan::New("FACE_FLAG_VERTICAL").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_VERTICAL));
  Nan::Set(target, Nan::New("FACE_FLAG_KERNING").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_KERNING));
  Nan::Set(target, Nan::New("FACE_FLAG_FAST_GLYPHS").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_FAST_GLYPHS));
  Nan::Set(target, Nan::New("FACE_FLAG_MULTIPLE_MASTERS").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_MULTIPLE_MASTERS));
  Nan::Set(target, Nan::New("FACE_FLAG_GLYPH_NAMES").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_GLYPH_NAMES));
  Nan::Set(target, Nan::New("FACE_FLAG_EXTERNAL_STREAM").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_EXTERNAL_STREAM));
  Nan::Set(target, Nan::New("FACE_FLAG_HINTER").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_HINTER));
  Nan::Set(target, Nan::New("FACE_FLAG_CID_KEYED").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_CID_KEYED));
  Nan::Set(target, Nan::New("FACE_FLAG_TRICKY").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_TRICKY));
  Nan::Set(target, Nan::New("FACE_FLAG_COLOR").ToLocalChecked(), Nan::New((uint32_t)FT_FACE_FLAG_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_STYLE_FLAG_XXX
  Nan::Set(target, Nan::New("STYLE_FLAG_ITALIC").ToLocalChecked(), Nan::New((uint32_t)FT_STYLE_FLAG_ITALIC));
  Nan::Set(target, Nan::New("STYLE_FLAG_BOLD").ToLocalChecked(), Nan::New((uint32_t)FT_STYLE_FLAG_BOLD));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Glyph_Format
  Nan::Set(target, Nan::New("GLYPH_FORMAT_NONE").ToLocalChecked(), Nan::New((uint32_t)FT_GLYPH_FORMAT_NONE));
  Nan::Set(target, Nan::New("GLYPH_FORMAT_COMPOSITE").ToLocalChecked(), Nan::New((uint32_t)FT_GLYPH_FORMAT_COMPOSITE));
  Nan::Set(target, Nan::New("GLYPH_FORMAT_BITMAP").ToLocalChecked(), Nan::New((uint32_t)FT_GLYPH_FORMAT_BITMAP));
  Nan::Set(target, Nan::New("GLYPH_FORMAT_OUTLINE").ToLocalChecked(), Nan::New((uint32_t)FT_GLYPH_FORMAT_OUTLINE));
  Nan::Set(target, Nan::New("GLYPH_FORMAT_PLOTTER").ToLocalChecked(), Nan::New((uint32_t)FT_GLYPH_FORMAT_PLOTTER));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Render_Mode
  Nan::Set(target, Nan::New("RENDER_MODE_NORMAL").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_NORMAL));
  Nan::Set(target, Nan::New("RENDER_MODE_LIGHT").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_LIGHT));
  Nan::Set(target, Nan::New("RENDER_MODE_MONO").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_MONO));
  Nan::Set(target, Nan::New("RENDER_MODE_LCD").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_LCD));
  Nan::Set(target, Nan::New("RENDER_MODE_LCD_V").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_LCD_V));
  Nan::Set(target, Nan::New("RENDER_MODE_MAX").ToLocalChecked(), Nan::New((uint32_t)FT_RENDER_MODE_MAX));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FSTYPE_XXX
  Nan::Set(target, Nan::New("FSTYPE_INSTALLABLE_EMBEDDING").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_INSTALLABLE_EMBEDDING));
  Nan::Set(target, Nan::New("FSTYPE_RESTRICTED_LICENSE_EMBEDDING").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING));
  Nan::Set(target, Nan::New("FSTYPE_PREVIEW_AND_PRINT_EMBEDDING").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING));
  Nan::Set(target, Nan::New("FSTYPE_EDITABLE_EMBEDDING").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_EDITABLE_EMBEDDING));
  Nan::Set(target, Nan::New("FSTYPE_NO_SUBSETTING").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_NO_SUBSETTING));
  Nan::Set(target, Nan::New("FSTYPE_BITMAP_EMBEDDING_ONLY").ToLocalChecked(), Nan::New((uint32_t)FT_FSTYPE_BITMAP_EMBEDDING_ONLY));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Pixel_Mode
  Nan::Set(target, Nan::New("PIXEL_MODE_NONE").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_NONE));
  Nan::Set(target, Nan::New("PIXEL_MODE_MONO").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_MONO));
  Nan::Set(target, Nan::New("PIXEL_MODE_GRAY").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_GRAY));
  Nan::Set(target, Nan::New("PIXEL_MODE_GRAY2").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_GRAY2));
  Nan::Set(target, Nan::New("PIXEL_MODE_GRAY4").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_GRAY4));
  Nan::Set(target, Nan::New("PIXEL_MODE_LCD").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_LCD));
  Nan::Set(target, Nan::New("PIXEL_MODE_LCD_V").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_LCD_V));
  Nan::Set(target, Nan::New("PIXEL_MODE_BGRA").ToLocalChecked(), Nan::New((uint32_t)FT_PIXEL_MODE_BGRA));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Size_Request_Type
  Nan::Set(target, Nan::New("SIZE_REQUEST_TYPE_NOMINAL").ToLocalChecked(), Nan::New((uint32_t)FT_SIZE_REQUEST_TYPE_NOMINAL));
  Nan::Set(target, Nan::New("SIZE_REQUEST_TYPE_REAL_DIM").ToLocalChecked(), Nan::New((uint32_t)FT_SIZE_REQUEST_TYPE_REAL_DIM));
  Nan::Set(target, Nan::New("SIZE_REQUEST_TYPE_BBOX").ToLocalChecked(), Nan::New((uint32_t)FT_SIZE_REQUEST_TYPE_BBOX));
  Nan::Set(target, Nan::New("SIZE_REQUEST_TYPE_CELL").ToLocalChecked(), Nan::New((uint32_t)FT_SIZE_REQUEST_TYPE_CELL));
  Nan::Set(target, Nan::New("SIZE_REQUEST_TYPE_SCALES").ToLocalChecked(), Nan::New((uint32_t)FT_SIZE_REQUEST_TYPE_SCALES));
}

FreeType2::~FreeType2() {
  FT_Done_FreeType(library);
}

NAN_METHOD(FreeType2::New_Memory_Face) {
  assert(info.Length() > 2);
  FT_Long length = (FT_Long)node::Buffer::Length(info[0].As<v8::Object>());
  FT_Byte* data = (FT_Byte*)malloc(length);
  memcpy(data, node::Buffer::Data(info[0].As<v8::Object>()), length);

  FT_Face ftFace;
  FT_Error err = FT_New_Memory_Face(
    library,
    data,
    length,
    ARG_TO_INT32(info[1]),
    &ftFace
  );

  if (!err) {
    v8::Local<v8::Object> fontFaceWrapper = Nan::NewInstance(FontFace::GetConstructor()).ToLocalChecked();
    FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(fontFaceWrapper);
    assert(fontFace->ftFace == 0);
    fontFace->ftFace = ftFace;
    assert(fontFace->ftFace != 0);
    fontFace->data = data;
    Nan::Set(Nan::To<v8::Object>(info[2]).ToLocalChecked(), Nan::New("face").ToLocalChecked(), fontFaceWrapper);
  } else {
    free(data);
  }

  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Select_Size) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Select_Size(fontFace->ftFace, ARG_TO_INT32(info[1]));
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Request_Size) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Size_RequestRec req = {
    static_cast<FT_Size_Request_Type>(ARG_TO_INT32(info[1])),
    static_cast<FT_Long>(ARG_TO_INT32(info[2])),
    static_cast<FT_Long>(ARG_TO_INT32(info[3])),
    static_cast<FT_UInt>(ARG_TO_INT32(info[4])),
    static_cast<FT_UInt>(ARG_TO_INT32(info[5]))
  };
  FT_Error err = FT_Request_Size(fontFace->ftFace, &req);
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Set_Char_Size) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Set_Char_Size(
    fontFace->ftFace,
    ARG_TO_INT32(info[1]),
    ARG_TO_INT32(info[2]),
    ARG_TO_INT32(info[3]),
    ARG_TO_INT32(info[4])
  );
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Set_Pixel_Sizes) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Set_Pixel_Sizes(
    fontFace->ftFace,
    ARG_TO_INT32(info[1]),
    ARG_TO_INT32(info[2])
  );
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Load_Glyph) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Load_Glyph(fontFace->ftFace, ARG_TO_INT32(info[1]), ARG_TO_INT32(info[2]));
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Load_Char) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Load_Char(fontFace->ftFace, ARG_TO_INT32(info[1]), ARG_TO_INT32(info[2]));
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Set_Transform) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Matrix matrix;
  FT_Vector delta;

  if (info[1]->IsArray()) {
    matrix.xx = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[1]).ToLocalChecked(), 0).ToLocalChecked());
    matrix.xy = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[1]).ToLocalChecked(), 1).ToLocalChecked());
    matrix.yx = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[1]).ToLocalChecked(), 2).ToLocalChecked());
    matrix.yy = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[1]).ToLocalChecked(), 3).ToLocalChecked());
  }

  if (info[2]->IsArray()) {
    delta.x = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[2]).ToLocalChecked(), 0).ToLocalChecked());
    delta.y = (FT_Fixed) TO_INT32(Nan::Get(Nan::To<v8::Object>(info[2]).ToLocalChecked(), 1).ToLocalChecked());
  }

  if (info[1]->IsArray() && info[2]->IsArray()) {
    FT_Set_Transform(fontFace->ftFace, &matrix, &delta);
  } else if (info[1]->IsArray()) {
    FT_Set_Transform(fontFace->ftFace, &matrix, 0);
  } else if (info[2]->IsArray()) {
    FT_Set_Transform(fontFace->ftFace, 0, &delta);
  } else {
    FT_Set_Transform(fontFace->ftFace, 0, 0);
  }
}

NAN_METHOD(FreeType2::Render_Glyph) {
  GlyphSlot* glyph = node::ObjectWrap::Unwrap<GlyphSlot>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Render_Glyph(glyph->ftGlyphSlot, static_cast<FT_Render_Mode>(ARG_TO_INT32(info[1])));
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Get_Kerning) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Vector kerning;
  FT_Error err = FT_Get_Kerning(
    fontFace->ftFace,
    ARG_TO_INT32(info[1]),
    ARG_TO_INT32(info[2]),
    ARG_TO_INT32(info[3]),
    &kerning
  );

  if (!err) {
    Nan::Set(Nan::To<v8::Object>(info[4]).ToLocalChecked(), Nan::New("x").ToLocalChecked(), Nan::New((int32_t)kerning.x));
    Nan::Set(Nan::To<v8::Object>(info[4]).ToLocalChecked(), Nan::New("y").ToLocalChecked(), Nan::New((int32_t)kerning.y));
  }

  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Select_Charmap) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Select_Charmap(fontFace->ftFace, static_cast<FT_Encoding>(ARG_TO_INT32(info[1])));
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Set_Charmap) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_Error err = FT_Set_Charmap(fontFace->ftFace, fontFace->ftFace->charmaps[ARG_TO_INT32(info[1])]);
  info.GetReturnValue().Set(Nan::New((int32_t)err));
}

NAN_METHOD(FreeType2::Get_Charmap_Index) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  info.GetReturnValue().Set(Nan::New((int32_t)FT_Get_Charmap_Index(fontFace->ftFace->charmap)));
}

NAN_METHOD(FreeType2::Get_Char_Index) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  info.GetReturnValue().Set(Nan::New((int32_t)FT_Get_Char_Index(fontFace->ftFace, ARG_TO_INT32(info[1]))));
}

NAN_METHOD(FreeType2::Get_First_Char) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_First_Char(fontFace->ftFace, &gindex);
  // v8::Local<v8::Object>::Cast(info[1])->Set(Nan::GetCurrentContext(), Nan::New("gindex").ToLocalChecked(), Nan::New((int32_t)gindex));
  Nan::Set(Nan::To<v8::Object>(info[1]).ToLocalChecked(), Nan::New("gindex").ToLocalChecked(), Nan::New((int32_t)gindex));
  info.GetReturnValue().Set(Nan::New((int32_t)charcode));
}

NAN_METHOD(FreeType2::Get_Next_Char) {
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Local<v8::Object>::Cast(info[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_Next_Char(fontFace->ftFace, ARG_TO_INT32(info[1]), &gindex);
  Nan::Set(Nan::To<v8::Object>(info[2]).ToLocalChecked(), Nan::New("gindex").ToLocalChecked(), Nan::New((int32_t)gindex));
  info.GetReturnValue().Set(Nan::New((int32_t)charcode));
}
