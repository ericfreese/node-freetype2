const freetype = require('..');
const fs = require('fs');
const Ajv = require('ajv');
const tsj = require("ts-json-schema-generator");

const tsjConfig = {
  path: "./module.d.ts",
  expose: "export",
  topRef: true
};

const FONT_PATH = __dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf'

const buffer = fs.readFileSync(FONT_PATH);
const schemaGenerator = tsj.createGenerator(tsjConfig)

const ajv = new Ajv({
  allErrors: true,
  extendRefs: 'fail',
});
const faceValidator = ajv.compile(schemaGenerator.createSchema('FontFaceProperties'));
const glyphBitmapValidator = ajv.compile(schemaGenerator.createSchema('GlyphBitmap'));
const glyphValidator = ajv.compile(schemaGenerator.createSchema('Glyph'));

function sanitiseProps(props) {
  // Process the props to clean off non json friendly types (eg Buffer)

  const res = {...props}
  Object.keys(res).forEach(k => {
    if (k === 'format' && res['bitmap'] !== undefined && typeof res[k] === 'number') {
      res[k] = 1 // GlyphFormat numbers are not sequential from 0, so generator gets confused
    } else if (res[k] === null) {
    } else if (Buffer.isBuffer(res[k])) {
      res[k] = {
        BYTES_PER_ELEMENT: res[k].BYTES_PER_ELEMENT,
        buffer: res[k].buffer,
        byteLength: res[k].byteLength,
        byteOffset: res[k].byteOffset,
        length: res[k].length,
      }
    } else if (Array.isArray(res[k])) {
      res[k] = res[k].map(sanitiseProps)
    } else if (typeof res[k] === 'object') {
      res[k] = sanitiseProps(res[k])
    }
  })
  return res
}

function validateSchema(validator, props) {
  const matches = validator(sanitiseProps(props));
  if (!matches) console.log('error', validator.errors)
  expect(matches).toBe(true);
}

describe('freetype2', function() {
    describe('NewFace', function() {
        it('matches the schema', function() {
          const face = freetype.NewFace(FONT_PATH, 0);
          validateSchema(faceValidator, face.properties());
        });
      });

    describe('NewMemoryFace', function() {
      it('matches the schema', function() {
        const face = freetype.NewMemoryFace(buffer, 0);
        validateSchema(faceValidator, face.properties());
      });

      it('invalid parameters', function () {
        expect(() => freetype.NewMemoryFace('', 0)).toThrow('Invalid buffer')
        expect(() => freetype.NewMemoryFace(Buffer.alloc(0), 'abc')).toThrow('Invalid faceIndex')
        expect(() => freetype.NewMemoryFace(Buffer.alloc(0))).toThrow('Invalid buffer')
        expect(() => freetype.NewMemoryFace(Buffer.alloc(5))).toThrow('invalid stream operation')
      })

      // Load it for use
      const face = freetype.NewMemoryFace(buffer, 0);
      expect(face).toBeTruthy()

      describe('getChar', function() {
        let lastChar
        it('getFirstChar', function() {
          lastChar = face.getFirstChar()
          expect(lastChar).toEqual({charCode: 32, glyphIndex: 1})
        })

        describe('getNextChar', function() {
          it('follow first', function() {
            lastChar = face.getNextChar(lastChar.charCode)
            expect(lastChar).toEqual({charCode: 33, glyphIndex: 2})
          })
          it('and again', function() {
            lastChar = face.getNextChar(lastChar.charCode)
            expect(lastChar).toEqual({charCode: 36, glyphIndex: 3})
          })

          it('from 0', function() {
            expect(face.getNextChar(0)).toEqual({charCode: 32, glyphIndex: 1})
          })
          it('from 65530', function() {
            expect(face.getNextChar(65530)).toBeNull()
          })

          it('with bad charCode', function() {
            expect(face.getNextChar(9.3)).toEqual({charCode: 32, glyphIndex: 1})
            expect(() => face.getNextChar('abc')).toThrow('charCode is not valid')
            expect(() => face.getNextChar()).toThrow('Not enough arguments')
            expect(() => face.getNextChar(undefined)).toThrow('charCode is not valid')
          })
        })

        it('getCharIndex', function() {
          expect(face.getCharIndex(0)).toEqual(null)
          expect(face.getCharIndex(-1)).toEqual(null)
          expect(face.getCharIndex(32)).toEqual(1)
          expect(face.getCharIndex(36)).toEqual(3)
          expect(face.getCharIndex(65530)).toEqual(null)
        })
      })

      describe('setCharSize', function() {
        it('should be ok with zeros', function() {
          face.setCharSize(0, 0, 0, 0)
          expect(face.properties().size).toEqual({
            "ascender": 64,
            "descender": -64,
            "height": 64,
            "maxAdvance": 64,
            "xScale": 4194,
            "xppem": 1,
            "yScale": 4194,
            "yppem": 1,
          })
          validateSchema(faceValidator, face.properties());

          // The below will all behave the same
          const expected = {
            "ascender": 128,
            "descender": -64,
            "height": 128,
            "maxAdvance": 128,
            "xScale": 5833,
            "xppem": 1,
            "yScale": 5833,
            "yppem": 1,
          }
          face.setCharSize(0, 10, 10, 10)
          expect(face.properties().size).toEqual(expected)

          face.setCharSize(10, 0, 10, 10)
          expect(face.properties().size).toEqual(expected)

          face.setCharSize(10, 10, 0, 10)
          expect(face.properties().size).toEqual(expected)

          face.setCharSize(10, 10, 10, 0)
          expect(face.properties().size).toEqual(expected)
        })
        it('sensible sizes', function() {
          face.setCharSize(15, 15, 72, 72)
          expect(face.properties().size).toEqual({
            "ascender": 896,
            "descender": -256,
            "height": 1088,
            "maxAdvance": 1024,
            "xScale": 62915,
            "xppem": 15,
            "yScale": 62915,
            "yppem": 15,
          })
          validateSchema(faceValidator, face.properties());

          face.setCharSize(103, 103, 64, 64)
          expect(face.properties().size).toEqual({
            "ascender": 5376,
            "descender": -1216,
            "height": 6592,
            "maxAdvance": 6400,
            "xScale": 384041,
            "xppem": 92,
            "yScale": 384041,
            "yppem": 92,
          })
        })

        it('bad parameters', function() {
          expect(() => face.setCharSize()).toThrow('Not enough arguments')
          expect(() => face.setCharSize(1, 2, 3)).toThrow('Not enough arguments')
          expect(() => face.setCharSize(undefined, 2, 3, 4)).toThrow('charWidth is not valid')
          expect(() => face.setCharSize(1, undefined, 3, 4)).toThrow('charHeight is not valid')
          expect(() => face.setCharSize(1, 2, undefined, 4)).toThrow('horzResolution is not valid')
          expect(() => face.setCharSize(1, 2, 3, undefined)).toThrow('vertResolution is not valid')
        })
      })
      describe('setPixelSizes', function() {
        it('should be ok with zeros', function() {
          face.setPixelSizes(0, 0)
          expect(face.properties().size).toEqual({
            "ascender": 64,
            "descender": -64,
            "height": 64,
            "maxAdvance": 64,
            "xScale": 4194,
            "xppem": 1,
            "yScale": 4194,
            "yppem": 1,
          })
          validateSchema(faceValidator, face.properties());

          // The below will all behave the same
          const expected = {
            "ascender": 640,
            "descender": -192,
            "height": 704,
            "maxAdvance": 704,
            "xScale": 41943,
            "xppem": 10,
            "yScale": 41943,
            "yppem": 10,
          }
          face.setPixelSizes(0, 10)
          expect(face.properties().size).toEqual(expected)

          face.setPixelSizes(10, 0)
          expect(face.properties().size).toEqual(expected)
        })
        it('sensible sizes', function() {
          face.setPixelSizes(15, 15)
          expect(face.properties().size).toEqual({
            "ascender": 896,
            "descender": -256,
            "height": 1088,
            "maxAdvance": 1024,
            "xScale": 62915,
            "xppem": 15,
            "yScale": 62915,
            "yppem": 15,
          })
          validateSchema(faceValidator, face.properties());

          face.setPixelSizes(103, 103)
          expect(face.properties().size).toEqual({
            "ascender": 6080,
            "descender": -1408,
            "height": 7360,
            "maxAdvance": 7232,
            "xScale": 432013,
            "xppem": 103,
            "yScale": 432013,
            "yppem": 103,
          })
        })

        it('bad parameters', function() {
          expect(() => face.setPixelSizes()).toThrow('Not enough arguments')
          expect(() => face.setPixelSizes(1)).toThrow('Not enough arguments')
          expect(() => face.setPixelSizes(undefined, 2)).toThrow('pixelWidth is not valid')
          expect(() => face.setPixelSizes(1, undefined)).toThrow('pixelHeight is not valid')
        })
      })

      describe('selectSize', function() {
        it('bad selections', function() {
          expect(() => face.selectSize(0)).toThrow('invalid face handle')
          expect(() => face.selectSize(-1)).toThrow('invalid face handle')
          expect(() => face.selectSize(undefined)).toThrow('strikeIndex is not valid')
          expect(() => face.selectSize()).toThrow('Not enough arguments')
        })

        // TODO - find and load a bitmap font to test this
      })

      describe('setTransform', function() {
        // ensure the face is setup ok
        face.setPixelSizes(18, 0)

        it('bad parameters', function() {
          face.setTransform(undefined, undefined)

          expect(() => face.setTransform(null, undefined)).toThrow('matrix is not valid')
          expect(() => face.setTransform([1,0,0], undefined)).toThrow('Not enough matrix components')
          face.setTransform([1,1,1,1], undefined)
          expect(() => face.setTransform([1,null,1,1], undefined)).toThrow('matrix.xy is not valid')

          expect(() => face.setTransform(undefined, null)).toThrow('delta is not valid')
          expect(() => face.setTransform(undefined, [1])).toThrow('Not enough delta components')
          expect(() => face.setTransform(undefined, [1, null])).toThrow('delta.y is not valid')
        })

        // TODO

      })

      describe('loadChar', function() {
        const face = freetype.NewMemoryFace(buffer, 0);
        expect(face).toBeTruthy()
        // ensure the face is setup ok
        face.setPixelSizes(0, 12)
        face.setTransform(undefined, undefined)

        it('bad parameters', function() {
          face.loadChar(0)
          face.loadChar(2 << 30)
          expect(() => face.loadChar()).toThrow('Not enough arguments')
          expect(() => face.loadChar(undefined)).toThrow('charCode is not valid')
          face.loadChar(0, undefined)
          expect(() => face.loadChar(0, null)).toThrow('loadFlags is not valid')
          face.loadChar(0, {})
          face.loadChar(0, {
            abc: true,
            pedantic: false,
            ignoreTransform: true
          })
        })

        it('load something', function() {
          const res = face.loadChar('a'.charCodeAt(0))
          validateSchema(glyphValidator, res)
          expect(res).toMatchSnapshot()
        })

        it('render something', function() {
          const rendered = face.loadChar('A'.charCodeAt(0), {
            render: true,
            loadTarget: freetype.RenderMode.MONO
          })
          validateSchema(glyphValidator, rendered)
          expect(rendered).toMatchSnapshot()

          expect(face.loadChar('D'.charCodeAt(0), {
            render: true,
            loadTarget: freetype.RenderMode.NORMAL
          })).toMatchSnapshot()
        })

        it('scale metrics', function() {
          const noScale = face.loadChar('A'.charCodeAt(0), {
            noScale: true
          })
          expect(noScale).not.toBeNull()
          validateSchema(glyphValidator, noScale)
          expect(noScale).toMatchSnapshot()

          const withScale = face.loadChar('D'.charCodeAt(0), {
            noScale: false
          })
          expect(withScale).not.toBeNull()
          validateSchema(glyphValidator, withScale)
          expect(withScale).toMatchSnapshot()
        })

      })

      describe('loadGlyph', function() {
        const face = freetype.NewMemoryFace(buffer, 0);
        expect(face).toBeTruthy()
        // ensure the face is setup ok
        face.setPixelSizes(18, 18)
        face.setTransform(undefined, undefined)

        it('bad parameters', function() {
          face.loadGlyph(0)
          expect(() => face.loadGlyph(2 << 30)).toThrow('invalid argument')
          expect(() => face.loadGlyph()).toThrow('Not enough arguments')
          expect(() => face.loadGlyph(undefined)).toThrow('glyphIndex is not valid')
          face.loadGlyph(0, undefined)
          expect(() => face.loadGlyph(0, null)).toThrow('loadFlags is not valid')
          face.loadGlyph(0, {})
          face.loadGlyph(0, {
            abc: true,
            pedantic: false,
            ignoreTransform: true
          })
        })

        it('load something', function() {
          const res = face.loadGlyph(5)
          validateSchema(glyphValidator, res)
          expect(res).toMatchSnapshot()
        })

        it('render something', function() {
          const rendered = face.loadGlyph(5, {
            render: true,
            loadTarget: freetype.RenderMode.MONO
          })
          validateSchema(glyphValidator, rendered)
          expect(rendered).toMatchSnapshot()

          expect(face.loadGlyph(5, {
            render: true,
            loadTarget: freetype.RenderMode.NORMAL
          })).toMatchSnapshot()
        })

        it('scale metrics', function() {
          const noScale = face.loadGlyph(5, {
            noScale: true
          })
          expect(noScale).not.toBeNull()
          validateSchema(glyphValidator, noScale)
          expect(noScale).toMatchSnapshot()

          const withScale = face.loadGlyph(6, {
            noScale: false
          })
          expect(withScale).not.toBeNull()
          validateSchema(glyphValidator, withScale)
          expect(withScale).toMatchSnapshot()
        })

      })

      describe('renderGlyph', function() {
        const face = freetype.NewMemoryFace(buffer, 0);
        expect(face).toBeTruthy()
        // ensure the face is setup ok
        face.setPixelSizes(18, 18)
        face.setTransform(undefined, undefined)
        expect(face.loadChar('A'.charCodeAt(0), { noBitmap: true }).bitmap).toBeNull()

        it('bad parameters', function() {
          expect(() => face.renderGlyph(-1)).toThrow('Invalid renderMode')
          expect(() => face.renderGlyph(67)).toThrow('Invalid renderMode')
        })

        it('ok', function() {
          const res = face.renderGlyph(0)
          validateSchema(glyphBitmapValidator, res)
          expect(res).toMatchSnapshot()

          const res2 = face.renderGlyph(1)
          validateSchema(glyphBitmapValidator, res2)
          expect(res2).toMatchSnapshot()

          const res3 = face.renderGlyph(2)
          validateSchema(glyphBitmapValidator, res3)
          expect(res3).toMatchSnapshot()
        })
      })

      describe('getKerning', function() {
        // TODO - it would be good to have some real numbers here
        expect(face.properties().faceFlags.kerning).toBeTruthy()
        it('bad parameters', function() {
          expect(face.getKerning(0, 0, 0)).toEqual({ x: 0, y: 0 })
          expect(face.getKerning(-1, 0, 0)).toEqual({ x: 0, y: 0 })

          expect(() => face.getKerning(5, 6, -1)).toThrow('Invalid kerningMode')
          expect(() => face.getKerning(5, 6, 5)).toThrow('Invalid kerningMode')
        })

        it ('ok', function() {
          const a = face.getCharIndex('A'.charCodeAt(0))
          const b = face.getCharIndex('B'.charCodeAt(0))
          expect(a).toBeTruthy()
          expect(b).toBeTruthy()

          expect(face.getKerning(a, b, 2)).toEqual({ x: 0, y: 0 })
        })
      })

    });

});