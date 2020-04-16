const freetype = require('../build/Release/freetype2');
const fs = require('fs');
const tv4 = require('tv4');

const schema = require('./schema');
const buffer = fs.readFileSync(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf');

describe('freetype2', function() {
    describe('NewFace', function() {
        // it('matches the schema', function() {
        //   const face = freetype.NewFace(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf', 0);
        //   const matches = tv4.validate(face.properties(), schema.FontFace);
        //   console.log('error', tv4.error)
        //   expect(matches).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
        // });
      });

    describe('NewMemoryFace', function() {
      // it('matches the schema', function() {
      //   const face = freetype.NewMemoryFace(buffer, 0);
      //   const matches = tv4.validate(face.properties(), schema.FontFace);
      //   console.log('error', tv4.error)
      //   expect(matches).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
      // });

      it('invalid parameters', function () {
        expect(() => freetype.NewMemoryFace('', 0)).toThrow('Invalid buffer')
        expect(() => freetype.NewMemoryFace(Buffer.alloc(0), 'abc')).toThrow('Invalid faceIndex')
        expect(() => freetype.NewMemoryFace(Buffer.alloc(0))).toThrow('invalid stream operation')
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

      describe('loadChar', function() {
        // ensure the face is setup ok
        face.setPixelSizes(18, 0)

        it('bad charCode', function() {
          // expect(() => face.loadChar(0)).toThrow('invalid size handle')
        })
      })


    });

});