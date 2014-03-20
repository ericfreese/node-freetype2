exports.FontFace = {
  type: 'object',
  properties: {
    num_faces:           { type: 'integer', required: true },
    face_index:          { type: 'integer', required: true },
    face_flags:          { type: 'integer', required: true },
    style_flags:         { type: 'integer', required: true },
    num_glyphs:          { type: 'integer', required: true },
    family_name:         { type: 'string', required: true },
    style_name:          { type: 'string', required: true },
    num_fixed_sizes:     { type: 'integer', required: true },
    num_available_sizes: { type: 'integer', required: true },
    num_charmaps:        { type: 'integer', required: true },
    bbox: {
      type: 'object',
      properties: {
        xMin: {
          type: 'integer',
          required: true
        },
        yMin: {
          type: 'integer',
          required: true
        },
        xMax: {
          type: 'integer',
          required: true
        },
        yMax: {
          type: 'integer',
          required: true
        }
      }
    },
    units_per_em:        { type: 'integer', required: true },
    ascender:            { type: 'integer', required: true },
    descender:           { type: 'integer', required: true },
    height:              { type: 'integer', required: true },
    max_advance_width:   { type: 'integer', required: true },
    max_advance_height:  { type: 'integer', required: true },
    underline_position:  { type: 'integer', required: true },
    underline_thickness: { type: 'integer', required: true },

    available_sizes: {
      type: 'array',
      required: true
    },
  }
};

exports.Glyph = {
  type: 'object',
  properties: {
    metrics: {
      type: 'object',
      properties: {
        width:        { type: 'integer', required: true },
        height:       { type: 'integer', required: true },
        horiBearingX: { type: 'integer', required: true },
        horiBearingY: { type: 'integer', required: true },
        horiAdvance:  { type: 'integer', required: true },
        vertBearingX: { type: 'integer', required: true },
        vertBearingY: { type: 'integer', required: true },
        vertAdvance:  { type: 'integer', required: true }
      }
    },

    linear_hori_advance: { type: 'integer', required: true },
    linear_vert_advance: { type: 'integer', required: true },
    lsb_delta:           { type: 'integer', required: true },
    rsb_delta:           { type: 'integer', required: true },
    format:              { type: 'integer', required: true }
  }
};
