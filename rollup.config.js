import babel from 'rollup-plugin-babel'
import commonJs from 'rollup-plugin-commonjs'
import uglify from 'rollup-plugin-uglify'

const config = {
  entry: 'src/index.js',
  format: 'umd',
  moduleName: 'SVGArcToCubicBezier',
  plugins: [
    babel({ exclude: 'node_modules/**' }),
    commonJs()
  ],
  sourceMap: true
}

if (process.env.NODE_ENV === 'production') {
  config.dest = 'dist/svg-points-to-cubic-bezier.min.js'
  config.plugins.push(uglify())
} else {
  config.dest = 'dist/svg-points-to-cubic-bezier.js'
}

export default config
