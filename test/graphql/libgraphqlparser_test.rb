require "test_helper"
require 'graphql/language/parser_tests'

describe GraphQL::Libgraphqlparser do
  include GraphQL::Language::ParserTests
  subject { GraphQL::Libgraphqlparser }
end
