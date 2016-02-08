# graphql-libgraphqlparser [![Build Status](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby.svg?branch=master)](https://travis-ci.org/rmosolgo/graphql-libgraphqlparser-ruby)

Make [`graphql`](https://github.com/rmosolgo/graphql-ruby) faster with [`libgraphqlparser`](https://github.com/graphql/libgraphqlparser). Ruby bindings to a C-level GraphQL parser.

```
~/projects/graphql-libgraphqlparser $ be ruby benchmark.rb
              user     system      total        real
Ruby      1.260000   0.010000   1.270000 (  1.272758)
C         0.000000   0.000000   0.000000 (  0.004207)
```

## Todo

- AbstractNode overrides are full of tension. Resolve that tension with GraphQL main.
