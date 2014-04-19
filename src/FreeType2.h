#ifndef NODE_FREETYPE2_FREETYPE2_H
#define NODE_FREETYPE2_FREETYPE2_H

#include <nan.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FreeType2 : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object> exports);

    static FT_Library library;

  private:
    explicit FreeType2();
    ~FreeType2();

    static NAN_METHOD(New_Memory_Face);
    static NAN_METHOD(Select_Size);
    static NAN_METHOD(Request_Size);
    static NAN_METHOD(Set_Char_Size);
    // static NAN_METHOD(Set_Pixel_Sizes);
    static NAN_METHOD(Load_Glyph);
    static NAN_METHOD(Load_Char);
    // static NAN_METHOD(Set_Transform);
    static NAN_METHOD(Render_Glyph);
    // static NAN_METHOD(Get_Kerning);
    // static NAN_METHOD(Get_Track_Kerning);
    // static NAN_METHOD(Get_Glyph_Name);
    // static NAN_METHOD(Get_Postscript_Name);
    static NAN_METHOD(Select_Charmap);
    static NAN_METHOD(Set_Charmap);
    static NAN_METHOD(Get_Charmap_Index);
    static NAN_METHOD(Get_Char_Index);
    static NAN_METHOD(Get_First_Char);
    static NAN_METHOD(Get_Next_Char);
    // static NAN_METHOD(Get_Name_Index);
    // static NAN_METHOD(Get_SubGlyph_Info);

};

#endif
