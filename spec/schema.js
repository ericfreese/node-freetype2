exports.FontFace = {
  type: 'object',
  properties: {
    num_faces:           { type: 'integer' },
    face_index:          { type: 'integer' },
    face_flags:          { type: 'integer' },
    style_flags:         { type: 'integer' },
    num_glyphs:          { type: 'integer' },
    family_name:         { type: 'string' },
    style_name:          { type: 'string' },
    available_sizes:     { type: 'array' },
    charmaps:            { type: 'array' },
    bbox: {
      type: 'object',
      properties: {
        xMin: { type: 'integer' },
        yMin: { type: 'integer' },
        xMax: { type: 'integer' },
        yMax: { type: 'integer' }
      },
      required: [ 'xMin', 'yMin', 'xMax', 'yMax' ]
    },
    units_per_EM:        { type: 'integer' },
    ascender:            { type: 'integer' },
    descender:           { type: 'integer' },
    height:              { type: 'integer' },
    max_advance_width:   { type: 'integer' },
    max_advance_height:  { type: 'integer' },
    underline_position:  { type: 'integer' },
    underline_thickness: { type: 'integer' },
  },
  required: [
    'num_faces',
    'face_index',
    'face_flags',
    'style_flags',
    'num_glyphs',
    'family_name',
    'style_name',
    'available_sizes',
    'charmaps',
    'bbox',
    'units_per_EM',
    'ascender',
    'descender',
    'height',
    'max_advance_width',
    'max_advance_height',
    'underline_position',
    'underline_thickness'
  ]
};

exports.Glyph = {
  type: 'object',
  properties: {
    metrics: {
      type: 'object',
      properties: {
        width:        { type: 'integer' },
        height:       { type: 'integer' },
        horiBearingX: { type: 'integer' },
        horiBearingY: { type: 'integer' },
        horiAdvance:  { type: 'integer' },
        vertBearingX: { type: 'integer' },
        vertBearingY: { type: 'integer' },
        vertAdvance:  { type: 'integer' }
      },
      required: [
        'width',
        'height',
        'horiBearingX',
        'horiBearingY',
        'horiAdvance',
        'vertBearingX',
        'vertBearingY',
        'vertAdvance'
      ]
    },

    linearHoriAdvance: { type: 'integer' },
    linearVertAdvance: { type: 'integer' },
    format:            { type: 'integer' },
    bitmap:            {
      type: 'object',
      properties: {
        rows:         { type: 'integer' },
        width:        { type: 'integer' },
        pitch:        { type: 'integer' },
        num_grays:    { type: 'integer' },
        pixel_mode:   { type: 'integer' },
      },
      required: [
        'rows',
        'width',
        'pitch',
        'buffer',
        'num_grays',
        'pixel_mode'
      ]
    },
    bitmap_left:       { type: 'integer' },
    bitmap_top:        { type: 'integer' },
    lsb_delta:         { type: 'integer' },
    rsb_delta:         { type: 'integer' }
  },
  required: [
    'metrics',
    'format',
    'bitmap',
    'bitmap_left',
    'bitmap_top',
    'lsb_delta',
    'rsb_delta'
  ]
};
