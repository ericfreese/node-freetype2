#ifndef NODE_FREETYPE2_FREETYPE2_H
#define NODE_FREETYPE2_FREETYPE2_H

#include <node.h>
#include <node_buffer.h>
#include <node_object_wrap.h>
#include <ft2build.h>
#include FT_FREETYPE_H

class FreeType2 : public node::ObjectWrap {
  public:
    static void Init(v8::Handle<v8::Object> exports);

    static FT_Library library;

  private:
    explicit FreeType2();
    ~FreeType2();

    static void New_Memory_Face(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Select_Size(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Request_Size(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Set_Char_Size(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Set_Pixel_Sizes(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Load_Glyph(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Load_Char(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Set_Transform(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Render_Glyph(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Get_Kerning(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Get_Track_Kerning(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Get_Glyph_Name(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Get_Postscript_Name(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Select_Charmap(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Set_Charmap(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Get_Charmap_Index(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Get_Char_Index(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Get_First_Char(const v8::FunctionCallbackInfo<v8::Value>& args);
    static void Get_Next_Char(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Get_Name_Index(const v8::FunctionCallbackInfo<v8::Value>& args);
    // static void Get_SubGlyph_Info(const v8::FunctionCallbackInfo<v8::Value>& args);

};

#endif
