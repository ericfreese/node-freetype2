#ifndef FONTFACE_H
#define FONTFACE_H

#include <node.h>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace v8;

class FontFace : public node::ObjectWrap {
  public:
    static void Init();
    static Handle<Value> NewInstance(const Arguments& args);

    FT_Face face;

  private:
    explicit FontFace(const FT_Byte* file_base, FT_Long file_size);
    ~FontFace();

    static Handle<Value> New(const Arguments& args);
    static Persistent<Function> constructor;

    static FT_Library library;
    void SetObjectProperties(Handle<Object> obj);
    Handle<Array> AvailableCharacters();
};

#endif