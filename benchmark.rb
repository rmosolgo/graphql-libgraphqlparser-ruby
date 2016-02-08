require 'benchmark'
require 'graphql'
require 'graphql/libgraphqlparser'

query_string = GraphQL::Introspection::INTROSPECTION_QUERY

Benchmark.bm(7) do |x|
  x.report("Ruby")   { 20.times { GraphQL.parse(query_string) } }
  x.report("C")      { 20.times { GraphQL::Libgraphqlparser.parse(query_string) } }
end
