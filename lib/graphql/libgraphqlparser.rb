require 'libgraphqlparser'
require 'graphql'
require 'graphql/libgraphqlparser/version'
require 'graphql/libgraphqlparser/ast_visitor'
module GraphQL
  module Libgraphqlparser
    def self.parse(query_string)
      parse_result = ::Libgraphqlparser::Parser.parse(query_string)
      visitor = GraphQL::Libgraphqlparser::ASTVisitor.new
      visitor.accept(parse_result)
      visitor.document
    end
  end
end
