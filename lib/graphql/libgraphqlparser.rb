require 'graphql'
require 'graphql/libgraphqlparser/builder'
require 'graphql/libgraphqlparser/monkey_patches/abstract_node'
require 'graphql/libgraphqlparser/version'
require_relative '../graphql_libgraphqlparser_ext'

module GraphQL
  module Libgraphqlparser
    def self.parse(string)
      begin
        builder = builder_parse(string)
        builder.document
      rescue ParseError => e
        error_message = e.message.match(/(\d+)\.(\d+): (.*)/)
        if error_message
          line = error_message[1].to_i
          col = error_message[2].to_i
          raise GraphQL::ParseError.new(error_message[3], line, col, string)
        else
          raise GraphQL::ParseError.new(e.message, nil, nil, string)
        end
      end
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
