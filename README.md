# graphql-libgraphqlparser [![Build Status](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby.svg?branch=master)](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby)

Make [`graphql`](https://github.com/rmosolgo/graphql-ruby) faster with [`libgraphqlparser`](https://github.com/graphql/libgraphqlparser). Ruby bindings to a C-level GraphQL parser.

It's faster:

```
~/projects/graphql-libgraphqlparser $ be ruby benchmark.rb
              user     system      total        real
Ruby      1.140000   0.010000   1.150000 (  1.161160)
C         0.000000   0.000000   0.000000 (  0.009008)
~/projects/graphql-libgraphqlparser $ be ruby benchmark.rb
              user     system      total        real
Ruby      1.180000   0.000000   1.180000 (  1.185929)
C         0.000000   0.000000   0.000000 (  0.008688)
~/projects/graphql-libgraphqlparser $ be ruby benchmark.rb
              user     system      total        real
Ruby      1.220000   0.010000   1.230000 (  1.233795)
C         0.010000   0.000000   0.010000 (  0.008584)
```

## Installation

This gem depends on [libgraphqlparser](https://github.com/graphql/libgraphqlparser). You can install it a few ways:

- __Homebrew__: `brew install libgraphqlparser`
- __From Source__:

  ```
  wget https://github.com/graphql/libgraphqlparser/archive/v0.4.0.tar.gz
  tar -xzvf v0.4.0.tar.gz
  cd libgraphqlparser-0.4.0/ && cmake . && make && make install
  ```

Then, install this gem:

```ruby
gem "graphql-libgraphqlparser"
```

When you `require` this gem, it overrides `GraphQL.parse`:

```ruby
require "graphql/libgraphqlparser"
```

## Todo

- AbstractNode overrides are full of tension. Resolve that tension with GraphQL main.
- Node `#type` is sometimes a String, sometimes a Node. That should always be the same.
