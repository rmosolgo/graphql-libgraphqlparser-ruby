require "test_helper"

LibgraphqlparserSuite = GraphQL::Compatibility::QueryParserSpecification.build_suite { |query_string|
  GraphQL::Libgraphqlparser.parse(query_string)
}
