require 'graphql'
require 'graphql/libgraphqlparser/builder'
require 'graphql/libgraphqlparser/monkey_patches/abstract_node'
require 'graphql/libgraphqlparser/version'
require_relative '../graphql_libgraphqlparser_ext'

module GraphQL
  module Libgraphqlparser
    def self.parse(string)
      builder = builder_parse(string)
      builder.document
    end
  end

  class << self
    def parse_with_libgraphqlparser(string)
      Libgraphqlparser.parse(string)
    end

    alias :parse_without_libgraphqlparser :parse

    def parse(string, as: nil)
      parse_with_libgraphqlparser(string)
    end
  end
end
