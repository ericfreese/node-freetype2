#include "FreeType2.h"
#include "FontFace.h"

void FreeType2::Init(v8::Handle<v8::Object> exports) {
  NanScope();

  FT_Init_FreeType(&library);

  FontFace::Init(exports);
  Glyph::Init(exports);

  char version[32];
  sprintf(version, "%i.%i.%i", FREETYPE_MAJOR, FREETYPE_MINOR, FREETYPE_PATCH);
  exports->Set(NanSymbol("version"), NanSymbol(version));

  NODE_SET_METHOD(exports, "New_Memory_Face", New_Memory_Face);
  NODE_SET_METHOD(exports, "Select_Size", Select_Size);
  NODE_SET_METHOD(exports, "Request_Size", Request_Size);
  NODE_SET_METHOD(exports, "Set_Char_Size", Set_Char_Size);
  // NODE_SET_METHOD(exports, "Set_Pixel_Sizes", Set_Pixel_Sizes);
  NODE_SET_METHOD(exports, "Load_Glyph", Load_Glyph);
  NODE_SET_METHOD(exports, "Load_Char", Load_Char);
  // NODE_SET_METHOD(exports, "Set_Transform", Set_Transform);
  NODE_SET_METHOD(exports, "Render_Glyph", Render_Glyph);
  // NODE_SET_METHOD(exports, "Get_Kerning", Get_Kerning);
  // NODE_SET_METHOD(exports, "Get_Track_Kerning", Get_Track_Kerning);
  // NODE_SET_METHOD(exports, "Get_Glyph_Name", Get_Glyph_Name);
  // NODE_SET_METHOD(exports, "Get_Postscript_Name", Get_Postscript_Name);
  NODE_SET_METHOD(exports, "Select_Charmap", Select_Charmap);
  NODE_SET_METHOD(exports, "Set_Charmap", Set_Charmap);
  NODE_SET_METHOD(exports, "Get_Charmap_Index", Get_Charmap_Index);
  NODE_SET_METHOD(exports, "Get_Char_Index", Get_Char_Index);
  NODE_SET_METHOD(exports, "Get_First_Char", Get_First_Char);
  NODE_SET_METHOD(exports, "Get_Next_Char", Get_Next_Char);
  // NODE_SET_METHOD(exports, "Get_Name_Index", Get_Name_Index);
  // NODE_SET_METHOD(exports, "Get_SubGlyph_Info", Get_SubGlyph_Info);

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Encoding
  exports->Set(NanSymbol("ENCODING_NONE"), v8::Integer::New(FT_ENCODING_NONE));
  exports->Set(NanSymbol("ENCODING_MS_SYMBOL"), v8::Integer::New(FT_ENCODING_MS_SYMBOL));
  exports->Set(NanSymbol("ENCODING_UNICODE"), v8::Integer::New(FT_ENCODING_UNICODE));
  exports->Set(NanSymbol("ENCODING_SJIS"), v8::Integer::New(FT_ENCODING_SJIS));
  exports->Set(NanSymbol("ENCODING_GB2312"), v8::Integer::New(FT_ENCODING_GB2312));
  exports->Set(NanSymbol("ENCODING_BIG5"), v8::Integer::New(FT_ENCODING_BIG5));
  exports->Set(NanSymbol("ENCODING_WANSUNG"), v8::Integer::New(FT_ENCODING_WANSUNG));
  exports->Set(NanSymbol("ENCODING_JOHAB"), v8::Integer::New(FT_ENCODING_JOHAB));
  exports->Set(NanSymbol("ENCODING_ADOBE_STANDARD"), v8::Integer::New(FT_ENCODING_ADOBE_STANDARD));
  exports->Set(NanSymbol("ENCODING_ADOBE_EXPERT"), v8::Integer::New(FT_ENCODING_ADOBE_EXPERT));
  exports->Set(NanSymbol("ENCODING_ADOBE_CUSTOM"), v8::Integer::New(FT_ENCODING_ADOBE_CUSTOM));
  exports->Set(NanSymbol("ENCODING_ADOBE_LATIN_1"), v8::Integer::New(FT_ENCODING_ADOBE_LATIN_1));
  exports->Set(NanSymbol("ENCODING_OLD_LATIN_2"), v8::Integer::New(FT_ENCODING_OLD_LATIN_2));
  exports->Set(NanSymbol("ENCODING_APPLE_ROMAN"), v8::Integer::New(FT_ENCODING_APPLE_ROMAN));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_LOAD_XXX
  exports->Set(NanSymbol("LOAD_DEFAULT"), v8::Integer::New(FT_LOAD_DEFAULT));
  exports->Set(NanSymbol("LOAD_NO_SCALE"), v8::Integer::New(FT_LOAD_NO_SCALE));
  exports->Set(NanSymbol("LOAD_NO_HINTING"), v8::Integer::New(FT_LOAD_NO_HINTING));
  exports->Set(NanSymbol("LOAD_RENDER"), v8::Integer::New(FT_LOAD_RENDER));
  exports->Set(NanSymbol("LOAD_NO_BITMAP"), v8::Integer::New(FT_LOAD_NO_BITMAP));
  exports->Set(NanSymbol("LOAD_VERTICAL_LAYOUT"), v8::Integer::New(FT_LOAD_VERTICAL_LAYOUT));
  exports->Set(NanSymbol("LOAD_FORCE_AUTOHINT"), v8::Integer::New(FT_LOAD_FORCE_AUTOHINT));
  exports->Set(NanSymbol("LOAD_CROP_BITMAP"), v8::Integer::New(FT_LOAD_CROP_BITMAP));
  exports->Set(NanSymbol("LOAD_PEDANTIC"), v8::Integer::New(FT_LOAD_PEDANTIC));
  exports->Set(NanSymbol("LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH"), v8::Integer::New(FT_LOAD_IGNORE_GLOBAL_ADVANCE_WIDTH));
  exports->Set(NanSymbol("LOAD_NO_RECURSE"), v8::Integer::New(FT_LOAD_NO_RECURSE));
  exports->Set(NanSymbol("LOAD_IGNORE_TRANSFORM"), v8::Integer::New(FT_LOAD_IGNORE_TRANSFORM));
  exports->Set(NanSymbol("LOAD_MONOCHROME"), v8::Integer::New(FT_LOAD_MONOCHROME));
  exports->Set(NanSymbol("LOAD_LINEAR_DESIGN"), v8::Integer::New(FT_LOAD_LINEAR_DESIGN));
  exports->Set(NanSymbol("LOAD_NO_AUTOHINT"), v8::Integer::New(FT_LOAD_NO_AUTOHINT));
  exports->Set(NanSymbol("LOAD_COLOR"), v8::Integer::New(FT_LOAD_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Kerning_Mode
  exports->Set(NanSymbol("KERNING_DEFAULT"), v8::Integer::New(FT_KERNING_DEFAULT));
  exports->Set(NanSymbol("KERNING_UNFITTED"), v8::Integer::New(FT_KERNING_UNFITTED));
  exports->Set(NanSymbol("KERNING_UNSCALED"), v8::Integer::New(FT_KERNING_UNSCALED));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FACE_FLAG_XXX
  exports->Set(NanSymbol("FACE_FLAG_SCALABLE"), v8::Integer::New(FT_FACE_FLAG_SCALABLE));
  exports->Set(NanSymbol("FACE_FLAG_FIXED_SIZES"), v8::Integer::New(FT_FACE_FLAG_FIXED_SIZES));
  exports->Set(NanSymbol("FACE_FLAG_FIXED_WIDTH"), v8::Integer::New(FT_FACE_FLAG_FIXED_WIDTH));
  exports->Set(NanSymbol("FACE_FLAG_SFNT"), v8::Integer::New(FT_FACE_FLAG_SFNT));
  exports->Set(NanSymbol("FACE_FLAG_HORIZONTAL"), v8::Integer::New(FT_FACE_FLAG_HORIZONTAL));
  exports->Set(NanSymbol("FACE_FLAG_VERTICAL"), v8::Integer::New(FT_FACE_FLAG_VERTICAL));
  exports->Set(NanSymbol("FACE_FLAG_KERNING"), v8::Integer::New(FT_FACE_FLAG_KERNING));
  exports->Set(NanSymbol("FACE_FLAG_FAST_GLYPHS"), v8::Integer::New(FT_FACE_FLAG_FAST_GLYPHS));
  exports->Set(NanSymbol("FACE_FLAG_MULTIPLE_MASTERS"), v8::Integer::New(FT_FACE_FLAG_MULTIPLE_MASTERS));
  exports->Set(NanSymbol("FACE_FLAG_GLYPH_NAMES"), v8::Integer::New(FT_FACE_FLAG_GLYPH_NAMES));
  exports->Set(NanSymbol("FACE_FLAG_EXTERNAL_STREAM"), v8::Integer::New(FT_FACE_FLAG_EXTERNAL_STREAM));
  exports->Set(NanSymbol("FACE_FLAG_HINTER"), v8::Integer::New(FT_FACE_FLAG_HINTER));
  exports->Set(NanSymbol("FACE_FLAG_CID_KEYED"), v8::Integer::New(FT_FACE_FLAG_CID_KEYED));
  exports->Set(NanSymbol("FACE_FLAG_TRICKY"), v8::Integer::New(FT_FACE_FLAG_TRICKY));
  exports->Set(NanSymbol("FACE_FLAG_COLOR"), v8::Integer::New(FT_FACE_FLAG_COLOR));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_STYLE_FLAG_XXX
  exports->Set(NanSymbol("STYLE_FLAG_ITALIC"), v8::Integer::New(FT_STYLE_FLAG_ITALIC));
  exports->Set(NanSymbol("STYLE_FLAG_BOLD"), v8::Integer::New(FT_STYLE_FLAG_BOLD));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Glyph_Format
  exports->Set(NanSymbol("GLYPH_FORMAT_NONE"), v8::Integer::New(FT_GLYPH_FORMAT_NONE));
  exports->Set(NanSymbol("GLYPH_FORMAT_COMPOSITE"), v8::Integer::New(FT_GLYPH_FORMAT_COMPOSITE));
  exports->Set(NanSymbol("GLYPH_FORMAT_BITMAP"), v8::Integer::New(FT_GLYPH_FORMAT_BITMAP));
  exports->Set(NanSymbol("GLYPH_FORMAT_OUTLINE"), v8::Integer::New(FT_GLYPH_FORMAT_OUTLINE));
  exports->Set(NanSymbol("GLYPH_FORMAT_PLOTTER"), v8::Integer::New(FT_GLYPH_FORMAT_PLOTTER));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Render_Mode
  exports->Set(NanSymbol("RENDER_MODE_NORMAL"), v8::Integer::New(FT_RENDER_MODE_NORMAL));
  exports->Set(NanSymbol("RENDER_MODE_LIGHT"), v8::Integer::New(FT_RENDER_MODE_LIGHT));
  exports->Set(NanSymbol("RENDER_MODE_MONO"), v8::Integer::New(FT_RENDER_MODE_MONO));
  exports->Set(NanSymbol("RENDER_MODE_LCD"), v8::Integer::New(FT_RENDER_MODE_LCD));
  exports->Set(NanSymbol("RENDER_MODE_LCD_V"), v8::Integer::New(FT_RENDER_MODE_LCD_V));
  exports->Set(NanSymbol("RENDER_MODE_MAX"), v8::Integer::New(FT_RENDER_MODE_MAX));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_FSTYPE_XXX
  exports->Set(NanSymbol("FSTYPE_INSTALLABLE_EMBEDDING"), v8::Integer::New(FT_FSTYPE_INSTALLABLE_EMBEDDING));
  exports->Set(NanSymbol("FSTYPE_RESTRICTED_LICENSE_EMBEDDING"), v8::Integer::New(FT_FSTYPE_RESTRICTED_LICENSE_EMBEDDING));
  exports->Set(NanSymbol("FSTYPE_PREVIEW_AND_PRINT_EMBEDDING"), v8::Integer::New(FT_FSTYPE_PREVIEW_AND_PRINT_EMBEDDING));
  exports->Set(NanSymbol("FSTYPE_EDITABLE_EMBEDDING"), v8::Integer::New(FT_FSTYPE_EDITABLE_EMBEDDING));
  exports->Set(NanSymbol("FSTYPE_NO_SUBSETTING"), v8::Integer::New(FT_FSTYPE_NO_SUBSETTING));
  exports->Set(NanSymbol("FSTYPE_BITMAP_EMBEDDING_ONLY"), v8::Integer::New(FT_FSTYPE_BITMAP_EMBEDDING_ONLY));

  // http://www.freetype.org/freetype2/docs/reference/ft2-basic_types.html#FT_Pixel_Mode
  exports->Set(NanSymbol("PIXEL_MODE_NONE"), v8::Integer::New(FT_PIXEL_MODE_NONE));
  exports->Set(NanSymbol("PIXEL_MODE_MONO"), v8::Integer::New(FT_PIXEL_MODE_MONO));
  exports->Set(NanSymbol("PIXEL_MODE_GRAY"), v8::Integer::New(FT_PIXEL_MODE_GRAY));
  exports->Set(NanSymbol("PIXEL_MODE_GRAY2"), v8::Integer::New(FT_PIXEL_MODE_GRAY2));
  exports->Set(NanSymbol("PIXEL_MODE_GRAY4"), v8::Integer::New(FT_PIXEL_MODE_GRAY4));
  exports->Set(NanSymbol("PIXEL_MODE_LCD"), v8::Integer::New(FT_PIXEL_MODE_LCD));
  exports->Set(NanSymbol("PIXEL_MODE_LCD_V"), v8::Integer::New(FT_PIXEL_MODE_LCD_V));
  exports->Set(NanSymbol("PIXEL_MODE_BGRA"), v8::Integer::New(FT_PIXEL_MODE_BGRA));

  // http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Size_Request_Type
  exports->Set(NanSymbol("SIZE_REQUEST_TYPE_NOMINAL"), v8::Integer::New(FT_SIZE_REQUEST_TYPE_NOMINAL));
  exports->Set(NanSymbol("SIZE_REQUEST_TYPE_REAL_DIM"), v8::Integer::New(FT_SIZE_REQUEST_TYPE_REAL_DIM));
  exports->Set(NanSymbol("SIZE_REQUEST_TYPE_BBOX"), v8::Integer::New(FT_SIZE_REQUEST_TYPE_BBOX));
  exports->Set(NanSymbol("SIZE_REQUEST_TYPE_CELL"), v8::Integer::New(FT_SIZE_REQUEST_TYPE_CELL));
  exports->Set(NanSymbol("SIZE_REQUEST_TYPE_SCALES"), v8::Integer::New(FT_SIZE_REQUEST_TYPE_SCALES));
}

FreeType2::~FreeType2() {
  FT_Done_FreeType(library);
}

NAN_METHOD(FreeType2::New_Memory_Face) {
  NanScope();
  FT_Face ftFace;
  FT_New_Memory_Face(library,
                     (FT_Byte*)node::Buffer::Data(args[0]->ToObject()),
                     (FT_Long)node::Buffer::Length(args[0]->ToObject()),
                     args[1]->Int32Value(),
                     &ftFace);
  v8::Handle<v8::Object> faceObj = NanPersistentToLocal(FontFace::constructor)->NewInstance();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(faceObj);
  fontFace->ftFace = ftFace;
  NanReturnValue(faceObj);
}

NAN_METHOD(FreeType2::Select_Size) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Select_Size(fontFace->ftFace, args[0]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Request_Size) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Size_RequestRec req = {
    static_cast<FT_Size_Request_Type>(args[1]->Int32Value()),
    args[2]->Int32Value(),
    args[3]->Int32Value(),
    args[4]->Int32Value(),
    args[5]->Int32Value()
  };
  FT_Request_Size(fontFace->ftFace, &req);
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Set_Char_Size) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Set_Char_Size(fontFace->ftFace,
                   args[1]->Int32Value(),
                   args[2]->Int32Value(),
                   args[3]->Int32Value(),
                   args[4]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Load_Glyph) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Load_Glyph(fontFace->ftFace, args[1]->Int32Value(), args[2]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Load_Char) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Load_Char(fontFace->ftFace, args[1]->Int32Value(), args[2]->Int32Value());
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Render_Glyph) {
  NanScope();
  Glyph* glyph = node::ObjectWrap::Unwrap<Glyph>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Render_Glyph(glyph->ftGlyph, static_cast<FT_Render_Mode>(args[1]->Int32Value()));
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Select_Charmap) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Select_Charmap(fontFace->ftFace, static_cast<FT_Encoding>(args[1]->Int32Value()));
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Set_Charmap) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_Set_Charmap(fontFace->ftFace, fontFace->ftFace->charmaps[args[1]->Int32Value()]);
  NanReturnUndefined();
}

NAN_METHOD(FreeType2::Get_Charmap_Index) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  NanReturnValue(v8::Integer::New(FT_Get_Charmap_Index(fontFace->ftFace->charmap)));
}

NAN_METHOD(FreeType2::Get_Char_Index) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  NanReturnValue(v8::Integer::New(FT_Get_Char_Index(fontFace->ftFace, args[1]->Int32Value())));
}

NAN_METHOD(FreeType2::Get_First_Char) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_First_Char(fontFace->ftFace, &gindex);
  v8::Handle<v8::Object>::Cast(args[1])->Set(NanSymbol("gindex"), v8::Integer::New(gindex));
  NanReturnValue(v8::Integer::New(charcode));
}

NAN_METHOD(FreeType2::Get_Next_Char) {
  NanScope();
  FontFace* fontFace = node::ObjectWrap::Unwrap<FontFace>(v8::Handle<v8::Object>::Cast(args[0]));
  FT_UInt gindex;
  FT_ULong charcode = FT_Get_Next_Char(fontFace->ftFace, args[1]->Int32Value(), &gindex);
  v8::Handle<v8::Object>::Cast(args[2])->Set(NanSymbol("gindex"), v8::Integer::New(gindex));
  NanReturnValue(v8::Integer::New(charcode));
}

FT_Library FreeType2::library;
