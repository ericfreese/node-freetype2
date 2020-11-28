const freetypeVersion = '2.10.1';
const freetypeName = `freetype-${freetypeVersion}`

const fs = require('fs-extra-plus')
const path = require('path')
const download = require('download')
const decompress = require('decompress');
const decompressTarxz = require('decompress-tarxz');


async function downloadFreetype() {

  const vendorPath = path.join(path.dirname(__dirname), "vendor")

  const versionHolderName = `.${freetypeName}`
  const versionHolderPath = path.join(vendorPath, versionHolderName)

  const downloadPath = path.join(vendorPath, `${freetypeName}.tar.xz`)
  const decompressedPath = path.join(vendorPath, freetypeName)
  const finalPath = path.join(vendorPath, "freetype")

    await fs.remove(finalPath)
    await fs.remove(fs.readdirSync(vendorPath)[0]) // version-holder
    await download(
      `https://downloads.sourceforge.net/project/freetype/freetype2/${freetypeVersion}/${freetypeName}.tar.xz`,
      vendorPath,
    );
    await decompress(downloadPath, vendorPath, {
        plugins: [
            decompressTarxz()
        ]
    });
    await fs.rename(decompressedPath, finalPath)
    await fs.writeFile(versionHolderPath, "")
    await fs.remove(downloadPath)
}

downloadFreetype()
