{
  'targets': [
    {
      'target_name': 'libfreetype',
      'type': 'static_library',
      'defines': [
        'FT2_BUILD_LIBRARY',
      ],
      'include_dirs': [
        '../vendor/freetype/include/',
      ],
      'sources': [
        # base components (required)
        '../vendor/freetype/src/base/ftsystem.c',
        '../vendor/freetype/src/base/ftinit.c',
        '../vendor/freetype/src/base/ftdebug.c',
        '../vendor/freetype/src/base/ftbase.c',

        '../vendor/freetype/src/base/ftbbox.c',       # recommended, see <freetype/ftbbox.h>
        '../vendor/freetype/src/base/ftglyph.c',      # recommended, see <freetype/ftglyph.h>

        '../vendor/freetype/src/base/ftbitmap.c',     # optional, see <freetype/ftbitmap.h>
        '../vendor/freetype/src/base/ftfstype.c',     # optional
        '../vendor/freetype/src/base/ftgasp.c',       # optional, see <freetype/ftgasp.h>
        '../vendor/freetype/src/base/ftlcdfil.c',     # optional, see <freetype/ftlcdfil.h>
        '../vendor/freetype/src/base/ftmm.c',         # optional, see <freetype/ftmm.h>
        '../vendor/freetype/src/base/ftpatent.c',     # optional
        '../vendor/freetype/src/base/ftstroke.c',     # optional, see <freetype/ftstroke.h>
        '../vendor/freetype/src/base/ftsynth.c',      # optional, see <freetype/ftsynth.h>
        '../vendor/freetype/src/base/fttype1.c',      # optional, see <freetype/t1tables.h>
        '../vendor/freetype/src/base/ftwinfnt.c',     # optional, see <freetype/ftwinfnt.h>
        '../vendor/freetype/src/base/ftxf86.c',       # optional, see <freetype/ftxf86.h>

        # font drivers (optional; at least one is needed)
        '../vendor/freetype/src/cff/cff.c',           # CFF/OpenType font driver
        '../vendor/freetype/src/sfnt/sfnt.c',         # SFNT files support (TrueType & OpenType)
        '../vendor/freetype/src/truetype/truetype.c', # TrueType font driver

        # rasterizers (optional; at least one is needed for vector formats)
        # '../vendor/freetype/src/raster/raster.c',     # monochrome rasterizer
        # '../vendor/freetype/src/smooth/smooth.c',     # anti-aliasing rasterizer

        # auxiliary modules (optional)
        '../vendor/freetype/src/autofit/autofit.c',   # auto hinting module
        '../vendor/freetype/src/pshinter/pshinter.c', # PS hinting module
        '../vendor/freetype/src/psnames/psnames.c',   # PostScript glyph names support
      ],
      'conditions': [
        [ 'OS=="mac"', {
          'sources': [
            '../vendor/freetype/src/base/ftmac.c',        # only on the Macintosh
          ],
        }],
      ],
      'direct_dependent_settings': {
        'include_dirs': [
          '../vendor/freetype/include',
        ],
      },
      'link_settings': {
        'libraries': [
          '-lfreetype',
        ],
      },
    }
  ]
}
