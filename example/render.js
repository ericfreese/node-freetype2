const fs = require('fs');
const sharp = require('sharp');
const freetype = require('..');

const face = freetype.NewMemoryFace(fs.readFileSync(__dirname + '/../spec/fonts/OpenBaskerville-0.0.53/OpenBaskerville-0.0.53.otf'));
face.setPixelSizes(40, 0);

(async function(){
    let img = sharp({
        create: {
        width: 500,
        height: 200,
        channels: 4,
        background: { r: 0, g: 120, b: 0, alpha: 1 }
        }
    })

    const layers = []

    let left = 50
    let top = 50

    const inputStr = 'Hello world'
    for (let i = 0; i < inputStr.length; i++) {
        const ch = face.loadChar(inputStr.charCodeAt(i), {
            render: true
        })

        if (ch.bitmap) {
            layers.push({
                input: ch.bitmap.buffer,
                top: top - (ch.metrics.horiBearingY / 64),
                left: left,
                blend: 'lighten',
                raw: {
                    width: ch.bitmap.width,
                    height: ch.bitmap.height,
                    channels: 1
                }
            })
        }
        left += ch.metrics.horiAdvance / 64
    }

    img = img.composite(layers)

    await img.toFile(__dirname + '/render-output.png')

})()