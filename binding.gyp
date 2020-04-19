{
  'targets': [
    {
      'target_name': 'freetype2',
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
      'dependencies': [
        'gyp/libfreetype.gyp:libfreetype'
      ],
      'sources': [
        'src/util.cc',
        'src/FreeType2.cc',
        'src/FontFace.cc',
        'src/enums.cc',
      ],
      'include_dirs': ["<!@(node -p \"require('node-addon-api').include\")"],

      'conditions': [
        ['OS=="mac"', {
          'cflags+': ['-fvisibility=hidden'],
          'xcode_settings': {
            'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
          }
        }]
      ]
    }
  ]
}
