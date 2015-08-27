var gulp = require('gulp');
var exec = require('child_process').exec;

gulp.task('clearconsole', function() {
  console.log("\033[2J\033[0f");
});

gulp.task('configure', function(cb) {
  exec('node-gyp configure', cb).stdout.pipe(process.stdout);
});

gulp.task('build', ['configure'], function(cb) {
  exec('node-gyp build', cb).stdout.pipe(process.stdout);
});

gulp.task('test', ['build'], function(cb) {
  exec('jasmine-node spec --growl', cb).stdout.pipe(process.stdout);
});

gulp.task('watch', function() {
  gulp.watch([ 'src/**', 'spec/**' ], [ 'clearconsole', 'test' ]);
});

gulp.task('default', [
  'watch',
  'test'
]);
