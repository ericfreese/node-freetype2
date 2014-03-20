var gulp = require('gulp'),
    sh = require('execSync');

gulp.task('clearconsole', function() {
  console.log("\033[2J\033[0f");
});

gulp.task('configure', function() {
  console.log(sh.exec('node-gyp configure').stdout);
});

gulp.task('build', function() {
  console.log(sh.exec('node-gyp build').stdout);
});

gulp.task('test', function() {
  console.log(sh.exec('jasmine-node spec --growl').stdout);
});

gulp.task('default', [ 'clearconsole', 'configure', 'build', 'test' ], function() {
  gulp.watch('src/**', [ 'clearconsole', 'build', 'test' ]);
  gulp.watch('spec/**', [ 'clearconsole', 'test' ]);
});

