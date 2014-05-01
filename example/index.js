var fs = require('fs'),
    ft = require('../build/Release/freetype2');

fs.readFile(process.argv[2], function(err, buffer) {
  if (!!err) throw err;

  // Create a font face
  var face = ft.New_Memory_Face(buffer, 0);

  // Get all available characters
  // See note at http://www.freetype.org/freetype2/docs/reference/ft2-base_interface.html#FT_Get_First_Char
  var getAvailableCharacters = function(face) {
    var gindex = {},
        charcode,
        chars = [];

    charcode = ft.Get_First_Char(face, gindex);
    while (gindex.gindex !== 0) {
      chars.push(charcode);
      charcode = ft.Get_Next_Char(face, charcode, gindex);
    }

    return chars;
  }

  var chars = getAvailableCharacters(face);
  console.log("Found "+chars.length+" available characters");

  //check if we have kerning in the font file
  if ( (face.face_flags & ft.FACE_FLAG_KERNING) === ft.FACE_FLAG_KERNING ) {
    var kernings = [];

    //need to set a size before asking for kerning...
    ft.Set_Char_Size(face, 100, 100, 1000, 1000);


    for (var i=0; i<chars.length; i++) {
      var left = ft.Get_Char_Index(face, chars[i]);

      for (var j=0; j<chars.length; j++) {
        var right = ft.Get_Char_Index(face, chars[j]);
        var kern = { x:0, y:0 };
        var err = ft.Get_Kerning(face, left, right, ft.KERNING_UNSCALED, kern);
        if (!err && kern.x !== 0) {
          kernings.push({
            left: left,
            right: right,
            value: kern.x
          });

        } 
      }
    }
    console.log("Found "+kernings.length+" kerning pairs");
  } else {
    console.warn("No kerning information in font file.");
  }

  ft.Set_Char_Size(face, 32 * 64, 32 * 64, 72, 72);

  //FT_GLYPH_FORMAT_OUTLINE
  ft.Load_Glyph(face, ft.Get_Char_Index(face, '.'.charCodeAt(0)), ft.LOAD_DEFAULT);
  if (face.glyph.format === ft.GLYPH_FORMAT_OUTLINE) {
    console.log("Glyph outline found.");

    ft.Outline_Decompose(face, {
      move_to: function(x, y) {
        console.log("move_to:", x, y);
      },
      line_to: function(x, y) {
        console.log("line_to:", x, y);
      },
      quad_to: function(cx, cy, x, y) {
        console.log("quad_to:", cx, cy, x, y);
      },
      cubic_to: function(cx1, cy1, cx2, cy2, x, y) {
        console.log("cubic_to:", cx1, cy1, cx2, cy2, x, y);
      },
    });
  }

});
