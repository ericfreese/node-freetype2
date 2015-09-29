var fs = require('fs');
var ft = require('../build/Release/freetype2');

var face = {};
ft.New_Memory_Face(fs.readFileSync(process.argv[2]), 0, face);
face = face.face;

var charCodes = 'ABCD'.split('').map(function(c) { return c.charCodeAt(0); });

ft.Set_Pixel_Sizes(face, 0, 12);
ft.Set_Transform(
  face,
  [ 0, -1 << 16, 1 << 16, 0 ],
  0
);

var renderBitmap = function(bitmap) {
  for (var i = 0; i < bitmap.buffer.length; i++) {
    if (i % bitmap.pitch === 0) console.log('');
    process.stdout.write(('        ' + bitmap.buffer.readUInt8(i).toString(2).replace(/0/g, ' ').replace(/1/g, '█')).substr(-8, 8));
  }

  console.log('');
};

var bitmaps = charCodes.map(function(ch) {
  ft.Load_Char(face, ch, ft.LOAD_DEFAULT);
  ft.Render_Glyph(face.glyph, ft.RENDER_MODE_MONO);
  return face.glyph.bitmap;
});

bitmaps.forEach(function(bmp) {
  renderBitmap(bmp);
});
