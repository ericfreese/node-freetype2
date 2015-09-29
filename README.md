# Node FreeType

[![NPM version](https://badge.fury.io/js/freetype2.png)](http://badge.fury.io/js/freetype2)
[![Build Status](https://travis-ci.org/ericfreese/node-freetype2.png?branch=master)](https://travis-ci.org/ericfreese/node-freetype2)

FreeType bindings for Node.js.

FreeType is a freely available software library to render fonts. http://www.freetype.org/

## Install

`npm install freetype2`

## Usage

``` javascript
var fs = require('fs'),
    ft = require('freetype2');

fs.readFile('/path/to/a/font.woff', function(err, buffer) {
  if (!!err) throw err;
  var face = {};
  var err = ft.New_Memory_Face(buffer, 0, face);
  if (!err) {
    face = face.face;
    console.log(face);
  }
});
```

The module exposes the following functions from FreeType:

``` javascript
ft.New_Memory_Face(buffer, face_index, aface);
ft.Select_Size(face, strike_index);
ft.Request_Size(face, type, width, height, horiResolution, vertResolution);
ft.Set_Char_Size(face, char_width, char_height, horz_resolution, vert_resolution);
ft.Set_Pixel_Sizes(face, pixel_width, pixel_height);
ft.Load_Glyph(face, glyph_index, load_flags);
ft.Load_Char(face, char_code, load_flags);
ft.Set_Transform(face, matrix, delta);
ft.Render_Glyph(slot, render_mode);
ft.Get_Kerning(face, left_glyph, right_glyph, kern_mode, akerning);
ft.Select_Charmap(face, encoding);
ft.Set_Charmap(face, charmap_index);
ft.Get_Charmap_Index(face);
ft.Get_Char_Index(face, charcode);
ft.Get_First_Char(face, agindex);
ft.Get_Next_Char(face, char_code, agindex);
```

See [FreeType documentation](http://www.freetype.org/freetype2/docs/reference/ft2-index.html) for more info.

## To do

- Glyph outline processing: http://www.freetype.org/freetype2/docs/reference/ft2-outline_processing.html
- Implement following methods:
    - `ft.Get_Track_Kerning`
    - `ft.Get_Glyph_Name`
    - `ft.Get_Postscript_Name`
    - `ft.Get_Name_Index`
    - `ft.Get_SubGlyph_Info`

---

Originally built for https://github.com/ericfreese/font-viewer.
