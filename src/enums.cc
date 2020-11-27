#include "enums.h"

void InitializeEnums(const Napi::Env& env, Napi::Object& exports) {
    Napi::Object renderMode = Napi::Object::New(env);
    renderMode.Set("NORMAL", static_cast<unsigned long>(FT_RENDER_MODE_NORMAL));
    renderMode.Set("LIGHT", static_cast<unsigned long>(FT_RENDER_MODE_LIGHT));
    renderMode.Set("MONO", static_cast<unsigned long>(FT_RENDER_MODE_MONO));
    renderMode.Set("LCD", static_cast<unsigned long>(FT_RENDER_MODE_LCD));
    renderMode.Set("LCD_V", static_cast<unsigned long>(FT_RENDER_MODE_LCD_V));
    exports.Set("RenderMode", renderMode);

    Napi::Object pixelMode = Napi::Object::New(env);
    pixelMode.Set("NONE", static_cast<unsigned long>(FT_PIXEL_MODE_NONE));
    pixelMode.Set("MONO", static_cast<unsigned long>(FT_PIXEL_MODE_MONO));
    pixelMode.Set("GRAY", static_cast<unsigned long>(FT_PIXEL_MODE_GRAY));
    pixelMode.Set("GRAY2", static_cast<unsigned long>(FT_PIXEL_MODE_GRAY2));
    pixelMode.Set("GRAY4", static_cast<unsigned long>(FT_PIXEL_MODE_GRAY4));
    pixelMode.Set("LCD", static_cast<unsigned long>(FT_PIXEL_MODE_LCD));
    pixelMode.Set("LCD_V", static_cast<unsigned long>(FT_PIXEL_MODE_LCD_V));
    pixelMode.Set("BGRA", static_cast<unsigned long>(FT_PIXEL_MODE_BGRA));
    exports.Set("PixelMode", pixelMode);

    Napi::Object kerningMode = Napi::Object::New(env);
    kerningMode.Set("DEFAULT", static_cast<unsigned long>(FT_KERNING_DEFAULT));
    kerningMode.Set("UNFITTED", static_cast<unsigned long>(FT_KERNING_UNFITTED));
    kerningMode.Set("UNSCALED", static_cast<unsigned long>(FT_KERNING_UNSCALED));
    exports.Set("KerningMode", kerningMode);

    Napi::Object glyphFormat = Napi::Object::New(env);
    glyphFormat.Set("NONE", static_cast<unsigned long>(FT_GLYPH_FORMAT_NONE));
    glyphFormat.Set("COMPOSITE", static_cast<unsigned long>(FT_GLYPH_FORMAT_COMPOSITE));
    glyphFormat.Set("BITMAP", static_cast<unsigned long>(FT_GLYPH_FORMAT_BITMAP));
    glyphFormat.Set("OUTLINE", static_cast<unsigned long>(FT_GLYPH_FORMAT_OUTLINE));
    glyphFormat.Set("PLOTTER", static_cast<unsigned long>(FT_GLYPH_FORMAT_PLOTTER));
    exports.Set("GlyphFormat", glyphFormat);

    Napi::Object sizeRequestType = Napi::Object::New(env);
    sizeRequestType.Set("NOMINAL", static_cast<unsigned long>(FT_SIZE_REQUEST_TYPE_NOMINAL));
    sizeRequestType.Set("REAL_DIM", static_cast<unsigned long>(FT_SIZE_REQUEST_TYPE_REAL_DIM));
    sizeRequestType.Set("BBOX", static_cast<unsigned long>(FT_SIZE_REQUEST_TYPE_BBOX));
    sizeRequestType.Set("CELL", static_cast<unsigned long>(FT_SIZE_REQUEST_TYPE_CELL));
    sizeRequestType.Set("SCALES", static_cast<unsigned long>(FT_SIZE_REQUEST_TYPE_SCALES));
    exports.Set("SizeRequestType", sizeRequestType);
}
