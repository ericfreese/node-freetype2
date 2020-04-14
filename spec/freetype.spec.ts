const freetype = require('../build/Release/freetype2');
const fs = require('fs');
const tv4 = require('tv4');

const schema = require('./schema');
const buffer = fs.readFileSync(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf');

describe('freetype2', function() {
    describe('NewFace', function() {
        it('matches the schema', function() {
            const face = freetype.NewFace(__dirname + '/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf', 0);
          const matches = tv4.validate(face.properties(), schema.FontFace);
          console.log('error', tv4.error)
          expect(matches).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
        });
      });

    describe('NewMemoryFace', function() {
      it('matches the schema', function() {
        const face = freetype.NewMemoryFace(buffer, 0);
        const matches = tv4.validate(face.properties(), schema.FontFace);
        console.log('error', tv4.error)
        expect(matches).toBe(true, !!tv4.error ? tv4.error.toString() : undefined);
      });
    });

});