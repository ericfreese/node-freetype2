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
  var face = ft.New_Memory_Face(buffer, 0);
  console.log(face);
});
```

The module exposes the following functions from FreeType:

    New_Memory_Face
    Select_Size
    Request_Size
    Set_Char_Size
    Load_Glyph
    Load_Char
    Render_Glyph
    Select_Charmap
    Set_Charmap
    Get_Charmap_Index
    Get_Char_Index
    Get_First_Char
    Get_Next_Char

### Coming Soon

    Set_Pixel_Sizes
    Set_Transform
    Get_Kerning
    Get_Track_Kerning
    Get_Glyph_Name
    Get_Postscript_Name
    Get_Name_Index
    Get_SubGlyph_Info

## To do

- Error checking. Throw type/argument and FreeType error exceptions.
- Glyph outline processing: http://www.freetype.org/freetype2/docs/reference/ft2-outline_processing.html

---

Originally built for https://github.com/ericfreese/font-viewer.
