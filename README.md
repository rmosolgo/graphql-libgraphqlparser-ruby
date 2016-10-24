# graphql-libgraphqlparser [![Build Status](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby.svg?branch=master)](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby) [![Gem Version](https://badge.fury.io/rb/graphql-libgraphqlparser.svg)](https://badge.fury.io/rb/graphql-libgraphqlparser)

Make [`graphql`](https://github.com/rmosolgo/graphql-ruby) faster with [`libgraphqlparser`](https://github.com/graphql/libgraphqlparser). Ruby bindings to a C-level GraphQL parser.

It's faster:

```
~/projects/graphql-libgraphqlparser $ bundle exec ruby benchmark.rb
              user     system      total        real
Ruby      0.090000   0.000000   0.090000 (  0.088713)
C         0.010000   0.000000   0.010000 (  0.012827)
~/projects/graphql-libgraphqlparser $ bundle exec ruby benchmark.rb
              user     system      total        real
Ruby      0.090000   0.010000   0.100000 (  0.090548)
C         0.010000   0.000000   0.010000 (  0.013126)
~/projects/graphql-libgraphqlparser $ bundle exec ruby benchmark.rb
              user     system      total        real
Ruby      0.080000   0.000000   0.080000 (  0.090066)
C         0.020000   0.000000   0.020000 (  0.011790)
~/projects/graphql-libgraphqlparser $ bundle show graphql
~/.rbenv/versions/2.1.0/lib/ruby/gems/2.1.0/gems/graphql-0.19.4
```

## Installation

This gem depends on [libgraphqlparser](https://github.com/graphql/libgraphqlparser) (>= 0.5.0). You can install it a few ways:

- Homebrew: `brew install libgraphqlparser`
- From Source:

  ```
  wget https://github.com/graphql/libgraphqlparser/archive/v0.5.0.tar.gz
  tar -xzvf v0.5.0.tar.gz
  cd libgraphqlparser-0.5.0/ && cmake . && make && make install
  ```

- With [`heroku-buildpack-libgraphqlparser`](https://github.com/goco-inc/heroku-buildpack-libgraphqlparser)

Then, install this gem:

```ruby
gem "graphql-libgraphqlparser"
```

When you `require` this gem, it overrides `GraphQL.parse`:

```ruby
require "graphql/libgraphqlparser"
```

## Libgraphqlparser versions

The Ruby gem expects certain versions of `libgraphqlparser` to be installed. I couldn't figure out how to check this in [`extconf.rb`](#), so I documented it here:

`libgraphqlparser` version | `graphql-libgraphqlparser`(Ruby gem)  version
----|----
>= 0.5.0 | 0.5.0
<= 0.4.0 | 0.4.0
