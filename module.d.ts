
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

export enum SizeRequestType {
    NOMINAL,
    REAL_DIM,
    BBOX,
    CELL,
    SCALES
}

export interface SizeRequest {
    type: SizeRequestType
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

    bbox: {
        xMin: number
        yMin: number
        xMax: number
        yMax: number
    }

    unitsPerEM: number
    ascender: number
    descender: number
    height: number

    maxAdvanceWidth: number
    maxAdvanceHeight: number
  
    underlinePosition: number
    underlineThickness: number
  
    size: {
        xppem: number
        yppem: number
        xScale: number
        yScale: number
        ascender: number
        descender: number
        height: number
        maxAdvance: number
    }

}

export enum RenderMode {
    NORMAL,
    LIGHT,
    MONO,
    LCD,
    LCD_V
}
export enum PixelMode {
    NONE,
    MONO,
    GRAY,
    GRAY2,
    GRAY4,
    LCD,
    LCD_V,
    BGRA
}
export enum KerningMode {
    DEFAULT,
    UNFITTED,
    UNSCALED
}

export interface GlyphBitmap {
    bitmap: {
        height: number
        width: number
        pitch: number
        buffer: Buffer
        pixelMode: PixelMode
        numGrays: number | null
    }
    bitmapLeft: number
    bitmapTop: number 
}

export enum GlyphFormat {
    NONE,
    COMPOSITE,
    BITMAP,
    OUTLINE,
    PLOTTER
}

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

    metrics: {
        isFontUnits: boolean
        width: number
        height: number
        horiBearingX: number
        horiBearingY: number
        horiAdvance: number
        vertBearingX: number
        vertBearingY: number
        vertAdvance: number
    }
    format: GlyphFormat
    lsbDelta: number
    rsbDelta: number
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

    loadGlyph(glyphIndex: number, loadFlags?: LoadFlags): Glyph
    loadChar(charCode: number, loadFlags?: LoadFlags): Glyph
    renderGlyph(renderMode: RenderMode): GlyphBitmap

    getKerning(leftGlyphIndex: number, rightGlyphIndex: number, kerningMode: KerningMode): Vector
    // getTrackKerning(pointSize: number, degree: number): number
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
