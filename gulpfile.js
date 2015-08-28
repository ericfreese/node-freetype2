var gulp = require('gulp');
var exec = require('child_process').exec;

gulp.task('clearconsole', function() {
  console.log("\033[2J\033[0f");
});

gulp.task('configure', function(cb) {
  exec('npm run-script configure', cb).stdout.pipe(process.stdout);
});

gulp.task('build', ['configure'], function(cb) {
  exec('npm run-script build', cb).stdout.pipe(process.stdout);
});

gulp.task('test', ['build'], function(cb) {
  exec('npm run-script test', cb).stdout.pipe(process.stdout);
});

gulp.task('watch', function() {
  gulp.watch([ 'src/**', 'spec/**' ], [ 'clearconsole', 'test' ]);
});

gulp.task('dev', [
  'watch',
  'test'
]);
