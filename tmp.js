const ft = require('.');

console.log(ft)

const face = ft.NewFace('./spec/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.ttf')
console.log(face, JSON.stringify(face))
console.log(face.numFaces, face.faceIndex, face.properties())
console.log(face.getCharIndex(56))
