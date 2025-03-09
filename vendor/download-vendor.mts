// script to download Freetype from https://sourceforge.net/projects/freetype/files/freetype2/

const freetypeVersion = '2.11.1';

import { existsSync } from 'fs';
import { rm, rename, writeFile, readFile } from 'fs/promises';
import glob from 'fast-glob'
import { DownloaderHelper } from 'node-downloader-helper';
import { decompress } from '@napi-rs/lzma/xz'
import * as tar from 'tar'

async function main() {
    const versionFile = ("./.vendor-version");
    const freeTypePath = "./freetype";
    const freetypeName = `freetype-${freetypeVersion}`

    if (
        existsSync(freeTypePath) &&
        existsSync(versionFile) &&
        freetypeName === await readFile(".vendor-version", "utf-8")
    ) {
        return;
    }

    // Clean up first
    await Promise.all([
        rm(versionFile, { recursive: true, force: true }),
        rm(freeTypePath, { recursive: true, force: true })
    ])

    // Download the Freetype tar.xz file
    const downloader = new DownloaderHelper(`https://downloads.sourceforge.net/project/freetype/freetype2/${freetypeVersion}/${freetypeName}.tar.xz`, "./")
    const ok = await downloader.start()
    if (!ok) {
        throw new Error("Failed to download freetype")
    }

    // decompress tar.xz 
    const tarXzBuffer = await readFile(downloader.getDownloadPath());
    const tarBuffer = await decompress(new Uint8Array(tarXzBuffer))
    const tarPath = "./freetype.tar"
    await writeFile(tarPath, new Uint8Array(tarBuffer))

    // untar
    await tar.x({
        file: tarPath,
        cwd: "./"
    })

    // Rename the extracted directory to "freetype"
    await rename(freetypeName, "freetype")

    // remove non-needed files
    await Promise.all([
        rm(tarPath, { recursive: true, force: true }),
        rm(`${freetypeName}.tar.xz`, { recursive: true, force: true }),
        // docs
        rm("./freetype/docs", { recursive: true, force: true }),
        // ChangeLog
        glob("ChangeLog*", { cwd: freeTypePath }).then(files => Promise.all(files.map(file => rm(file, { force: true })))),
        // clang-format
        rm("./freetype/.clang-format", { recursive: true, force: true }),
        // builds
        rm("./freetype/builds", { recursive: true, force: true })
    ])

    // Write the version to the version file
    await writeFile(".vendor-version", freetypeName)
}

await main()
