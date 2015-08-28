var fs = require('fs'),
    tv4 = require('tv4'),
    ft = require('../build/Release/freetype2'),
    schema = require('./schema'),
    buffer = fs.readFileSync(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf');

describe('FontFace from New_Memory_Face', function() {
  it('matches the schema', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    expect(tv4.validate(f, schema.FontFace)).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
  });
});

describe('#Get_Char_Index', function() {
  it('returns the correct glyph index', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    expect(ft.Get_Char_Index(f, 'A'.charCodeAt(0))).toBe(28);
  });
});

describe('#Get_Kerning', function() {
  it('returns the correct kerning', function() {
    var face = ft.New_Memory_Face(buffer, 0);
    ft.Set_Char_Size(face, 100, 100, 1000, 1000);

    var left = ft.Get_Char_Index(face, 'y'.charCodeAt(0));
    var right = ft.Get_Char_Index(face, 'b'.charCodeAt(0));
    var obj = {};
    var err = ft.Get_Kerning(face, left, right, ft.KERNING_UNSCALED, obj);
    expect(err).toBe(0);
    expect(obj.x).toBe(-43);
    expect(obj.y).toBe(0);
  });
});

describe('#Load_Glyph', function() {
  it('matches the schema', function() {
    var f = ft.New_Memory_Face(buffer, 0);
    ft.Load_Glyph(f, 28, ft.LOAD_NO_SCALE);
    expect(tv4.validate(f.glyph, schema.Glyph)).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
  });
});
