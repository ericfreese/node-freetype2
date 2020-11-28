// script to automatically download vendor files from // from https://sourceforge.net/projects/freetype/files/freetype2/

const freetypeVersion = '2.10.4';
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

  if (
    !fs.existsSync(vendorPath) ||
    !fs.existsSync(finalPath) ||
    !fs.existsSync(versionHolderPath) ||
    versionHolderName !== fs.readdirSync(vendorPath)[0] // version holders don't match
  ) {
    await fs.remove(fs.readdirSync(vendorPath)[0]) // version-holder
    await fs.remove(finalPath)
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

    // remove not needed files
    // docs
    await fs.remove(path.join(finalPath, "docs"))
    // ChangeLog
    const ChangeLogFiles = await fs.glob("ChangeLog*", finalPath)
    for (const file of ChangeLogFiles) {
      await fs.remove(file)
    }
    // clang-format
    await fs.remove(path.join(finalPath, ".clang-format"))

    // builds
    await fs.remove(path.join(finalPath, "builds"))
  }
}

downloadFreetype()
