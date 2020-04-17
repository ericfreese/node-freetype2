const fs = require('fs');
const freetype = require('..');

const face = freetype.NewMemoryFace(fs.readFileSync(__dirname + '/../spec/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf'));

const charCodes = 'ABCD'.split('').map(c => c.charCodeAt(0));

// Give it some size
face.setPixelSizes(0, 12);
// Rotate 90CCW
face.setTransform(
  [ 0, -1 << 16, 1 << 16, 0 ],
  undefined
);

function renderBitmap(bitmap) {
  for (var i = 0; i < bitmap.buffer.length; i++) {
    if (i % bitmap.pitch === 0) console.log('');
    process.stdout.write(('        ' + bitmap.buffer.readUInt8(i).toString(2).replace(/0/g, ' ').replace(/1/g, '█')).substr(-8, 8));
  }

  console.log('');
};

charCodes.forEach((ch) => {
  const glyph = face.loadChar(ch, {
    render: true,
    loadTarget: 2 // Mono
  });

  renderBitmap(glyph.bitmap);
});
