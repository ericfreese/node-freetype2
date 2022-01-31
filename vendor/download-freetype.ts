// script to automatically download vendor files from // from https://sourceforge.net/projects/freetype/files/freetype2/

const freetypeVersion = '2.10.4';
const freetypeName = `freetype-${freetypeVersion}`

import { existsSync, readdirSync, remove, rename, writeFile } from 'fs-extra';
import glob from 'fast-glob'
import { join, dirname } from 'path';
import download from 'download';
import decompress from 'decompress';
// @ts-ignore
import decompressTarxz from 'decompress-tarxz';


async function downloadFreetype() {
  const vendorPath = join(dirname(__dirname), "vendor")

  const versionHolderName = `.${freetypeName}`
  const versionHolderPath = join(vendorPath, versionHolderName)

  const downloadPath = join(vendorPath, `${freetypeName}.tar.xz`)
  const decompressedPath = join(vendorPath, freetypeName)
  const finalPath = join(vendorPath, "freetype")

  if (
    !existsSync(vendorPath) ||
    !existsSync(finalPath) ||
    !existsSync(versionHolderPath) ||
    versionHolderName !== readdirSync(vendorPath)[0] // version holders don't match
  ) {
    await remove(readdirSync(vendorPath)[0]) // version-holder
    await remove(finalPath)
    await download(
      `https://downloads.sourceforge.net/project/freetype/freetype2/${freetypeVersion}/${freetypeName}.tar.xz`,
      vendorPath,
    );
    await decompress(downloadPath, vendorPath, {
      plugins: [
        decompressTarxz()
      ]
    });
    await rename(decompressedPath, finalPath)
    await writeFile(versionHolderPath, "")
    await remove(downloadPath)

    // remove not needed files
    // docs
    await remove(join(finalPath, "docs"))
    // ChangeLog
    const ChangeLogFiles = await glob("ChangeLog*", { cwd: finalPath })
    for (const file of ChangeLogFiles) {
      await remove(file)
    }
    // clang-format
    await remove(join(finalPath, ".clang-format"))

    // builds
    await remove(join(finalPath, "builds"))
  }
}

downloadFreetype()
