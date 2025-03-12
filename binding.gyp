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
        ['OS == "linux" or OS == "freebsd" or OS == "openbsd" or OS == "solaris"', {
          'cflags_cc!': [
            '-std=gnu++0x',
            '-std=gnu++1y',
            '-std=gnu++17'
          ],
          'cflags_cc+': [
            '-std=c++17',
            '-fvisibility=hidden',
          ],
          'cflags+': [
            '-fvisibility=hidden',
          ],
        }],
        ['OS == "mac"', {
          'xcode_settings': {
            'CLANG_CXX_LANGUAGE_STANDARD': 'c++17',
            'GCC_SYMBOLS_PRIVATE_EXTERN': 'YES', # -fvisibility=hidden
          },
        }],
        ['OS == "win"', {
          'msvs_settings': {
            'VCCLCompilerTool': {
              'AdditionalOptions': [
                '-std:c++17'
              ],
            }
          },
        }],
          
      ],
    }
  ]
}
