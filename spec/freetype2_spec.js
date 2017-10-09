var fs = require('fs'),
    tv4 = require('tv4'),
    ft = require('../build/Release/freetype2'),
    schema = require('./schema'),
    buffer = fs.readFileSync(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf');

describe('freetype2', function() {
  describe('#New_Memory_Face', function() {
    it('matches the schema', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      expect(err).toBe(0);
      face = face.face;
      expect(tv4.validate(face, schema.FontFace)).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
    });
  });

  describe('#Get_Char_Index', function() {
    it('returns the correct glyph index', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      expect(ft.Get_Char_Index(face, 'A'.charCodeAt(0))).toBe(28);
    });
  });

  describe('#Set_Pixel_Sizes', function() {
    it('succeeds', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      err = ft.Set_Pixel_Sizes(face, 12, 12);
      expect(err).toBe(0);
    });
  });

  describe('#Set_Transform', function() {
    it('succeeds', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      ft.Set_Transform(
        face,
        [ 0, -1 << 16, 1 << 16, 0 ],
        [ 40 << 6, 20 << 6 ]
      );
    });
  });

  describe('#Load_Glyph', function() {
    it('matches the schema', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      ft.Load_Glyph(face, 28, ft.LOAD_DEFAULT);
      expect(tv4.validate(face.glyph, schema.Glyph)).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
    });
  });

  describe('#Render_Glyph', function() {
    it('bitmap buffer length should equal its pitch multiplied by the number of rows', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      ft.Set_Char_Size(face, 0, 40 << 6, 0, 0);
      ft.Load_Glyph(face, 28, ft.LOAD_DEFAULT);
      ft.Render_Glyph(face.glyph, ft.RENDER_MODE_MONO);
      expect(face.glyph.bitmap.buffer.length).toBe(face.glyph.bitmap.pitch * face.glyph.bitmap.rows);
    });
  });

  describe('#Get_Kerning', function() {
    it('returns the correct kerning', function() {
      var face = {};
      var err = ft.New_Memory_Face(buffer, 0, face);
      face = face.face;
      ft.Set_Char_Size(face, 0, 40 << 6, 0, 0);
      var kerning = {};
      var err = ft.Get_Kerning(
        face,
        ft.Get_Char_Index(face, 'y'.charCodeAt(0)),
        ft.Get_Char_Index(face, 'b'.charCodeAt(0)),
        ft.KERNING_UNSCALED,
        kerning
      );
      expect(err).toBe(0);
      expect(kerning.x).toBe(-43);
      expect(kerning.y).toBe(0);
    });
  });
});
