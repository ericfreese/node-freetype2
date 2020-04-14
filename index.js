const ft = require('./build/Release/freetype2');

console.log(ft)

const face = ft.NewFace('./spec/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.ttf')
console.log(face, JSON.stringify(face))
console.log(face.numFaces, face.faceIndex)
console.log(face.getCharIndex(56))
