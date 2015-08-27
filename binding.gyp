{
  'targets': [
    {
      'target_name': 'freetype2',
      'dependencies': [
        'gyp/libfreetype.gyp:libfreetype'
      ],
      'sources': [
        'src/init.cc',
        'src/FreeType2.cc',
        'src/FontFace.cc',
        'src/GlyphSlot.cc'
      ],
      "include_dirs" : [
        "<!(node -e \"require('nan')\")"
      ],
    }
  ]
}
