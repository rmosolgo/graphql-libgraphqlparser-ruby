require 'graphql'
require 'graphql/libgraphqlparser/builder'
require 'graphql/libgraphqlparser/monkey_patches/abstract_node'
require 'graphql/libgraphqlparser/version'
require_relative '../graphql_libgraphqlparser_ext'

module GraphQL
  module Libgraphqlparser
    def self.parse(string, tracer: GraphQL::Tracing::NullTracer)
      tracer.trace("parse", { query_string: string }) do
        begin
          builder = builder_parse(string)
          builder.document
        rescue ArgumentError
          if index = string.index("\x00")
            string_before_null = string.slice(0, index)
            line = string_before_null.count("\n") + 1
            col = index - (string_before_null.rindex("\n") || 0)
            raise GraphQL::ParseError.new("Invalid null byte in query", line, col, string)
          end
          raise
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
  end

  class << self
    def parse_with_libgraphqlparser(*args)
      Libgraphqlparser.parse(*args)
    end

    alias :parse_without_libgraphqlparser :parse

    def parse(*args)
      parse_with_libgraphqlparser(*args)
    end
  end
end
