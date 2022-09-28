// Will load a compiled build if present or a prebuild.
// If no build if found it will throw an exception
module.exports = require("pkg-prebuilds/bindings")(
  __dirname,
  require("./binding-options")
);
