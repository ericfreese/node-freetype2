
export interface LoadFlags {
    noScale?: boolean
    noHinting?: boolean
    render?: boolean
    noBitmap?: boolean
    verticalLayout?: boolean
    forceAutohint?: boolean
    pedantic?: boolean
    noRecurse?: boolean
    ignoreTransform?: boolean
    monochrome?: boolean
    linearDesign?: boolean
    noAutohint?: boolean
    loadTarget?: RenderMode
    color?: boolean
    computeMetrics?: boolean
    bitmapMetricsOnly?: boolean
}

export const FreeTypeVersion: string;

export interface SizeRequest {
    type: number // TODO - enum
    width: number
    height: number
    horiResolution: number
    vertResolution: number
}

export type Matrix = [ number, number, number, number ]
export type Vector = [ number, number ]

export interface Char {
    charCode: number
    glyphIndex: number
}

export interface FontFaceProperties {
    numFaces: number
    faceIndex: number

    faceFlags: {
        scalable: boolean
        fixedSizes: boolean
        fixedWidth: boolean
        sfnt: boolean
        horizontal: boolean
        vertical: boolean
        kerning: boolean
        multipleMasters: boolean
        glyphNames: boolean
        externalStream: boolean
        hinter: boolean
        cidKeyed: boolean
        tricky: boolean
        color: boolean
        variation: boolean
    }

    styleFlags: {
        italic: boolean
        bold: boolean
    }
  
    numGlyphs: number
    familyName: string
    styleName: string

    availableSizes: Array<{
        height: number
        width: number
        size: number
        xppem: number
        yppem: number
    }>

}

export type KerningMode = number // TODO - properly
export type RenderMode = number // TODO - properly
export type PixelMode = number // TODO - properly

export interface Glyph {
    bitmap: {
        height: number
        width: number
        pitch: number
        buffer: Buffer
        pixelMode: PixelMode
        numGrays: number | null
    } | null
    bitmapLeft: number | null
    bitmapTop: number | null 
}

export class FontFace {
    properties(): FontFaceProperties

    setCharSize(charWidth: number, charHeight: number, horzResolution: number, vertResolution: number): void
    setPixelSizes(pixelWidth: number, pixelHeight: number): void
    // requestSize(props: SizeRequest): void
    selectSize(strikeIndex: number): void
    setTransform(matrix?: Matrix, vector?: Vector): void

    getCharIndex(charCode: number): number | null
    getFirstChar(): Char | null
    getNextChar(charCode: number): Char | null
    // getNameIndex

    loadGlyph(glyphIndex: number, loadFlags?: LoadFlags): void
    loadChar(charCode: number, loadFlags?: LoadFlags): void
    renderGlyph(renderMode: RenderMode): void

    getKerning(leftGlyphIndex: number, rightGlyphIndex: number, kerningMode: KerningMode): Vector
    getTrackKerning(pointSize: number, degree: number): number
    // getGlyphName
    // getPostscriptName
    // selectCharmap
    // setCharmap
    // getCharmapIndex
    // getFSTypeFlags
    // getSubGlyphInfo
}

export function NewFace(filepath: string, faceIndex?: number): FontFace;
export function NewMemoryFace(buffer: Buffer, faceIndex?: number): FontFace;
