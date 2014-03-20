var fs = require('fs'),
    tv4 = require('tv4'),
    ft = require('../build/Release/freetype2'),
    schema = require('./schema'),
    buffer = fs.readFileSync(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf');

describe('#New_Memory_Face', function() {
  it('matches the schema', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    expect(tv4.validate(f, schema.FontFace)).toBe(true);
  });
});

describe('#Get_Char_Index', function() {
  it('returns the correct glyph index', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    expect(ft.Get_Char_Index(f, 'A'.charCodeAt(0))).toBe(28);
  });
});

describe('#Load_Glyph', function() {
  it('matches the schema', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    ft.Load_Glyph(f, 28, ft.LOAD_NO_SCALE);
    expect(tv4.validate(f.glyph, schema.Glyph)).toBe(true);
  });
});
