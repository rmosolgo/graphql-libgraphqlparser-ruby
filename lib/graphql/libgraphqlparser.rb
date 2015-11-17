require 'graphql'
require 'graphql/libgraphqlparser/builder'
require 'graphql/libgraphqlparser/libgraphqlparser'
require 'graphql/libgraphqlparser/monkey_patches/abstract_node'
require 'graphql/libgraphqlparser/version'

module GraphQL
  module Libgraphqlparser
    def self.parse(string)
      builder = builder_parse(string)
      builder.document
    end
  end
end
