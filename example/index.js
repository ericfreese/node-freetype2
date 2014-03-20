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

  console.log(getAvailableCharacters(face));
});
