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

  if ( ft.HAS_KERNING(face) ) {
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
});
