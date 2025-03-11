const path = require('path');
module.exports = {
  context: path.resolve(__dirname, ''),
  entry: {
    index: './sankey.js'
  },
  output: {
    path: path.resolve(__dirname, ''),
    filename: './sankey_webpack.js',
  },
  module: {      // add this
    rules: [
      {
        test: /\.m?js$/,
        exclude: /(node_modules|bower_components)/,
        use: {
          loader: 'babel-loader',
          options: {
            presets: ['@babel/preset-env']
          }
        }
      }
    ]
  }
}
