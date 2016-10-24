module GraphQL
  module Libgraphqlparser
    # Keeps a stack of parse results, exposing the latest one.
    # The C parser can call methods on this object, assuming
    # they'll be applied to the right object.
    class Builder
      include GraphQL::Language

      def initialize
        @ast_stack = []
      end

      def document
        @ast_stack.first
      end

      def current
        @ast_stack.last
      end

      def begin_visit(node_class_name)
        # p "--> BEGIN #{node_class_name}"
        node_class = Nodes.const_get(node_class_name)
        node = node_class.new
        case node
        when Nodes::OperationDefinition, Nodes::FragmentDefinition
          current.definitions << node
        when Nodes::VariableDefinition
          current.variables << node
        when Nodes::VariableIdentifier
          if current.is_a?(Nodes::VariableDefinition)
            node = current
          else
            current.value = node
          end
        when Nodes::Directive
          current.directives << node
        when Nodes::Argument
          current.arguments << node
        when Nodes::InlineFragment, Nodes::FragmentSpread, Nodes::Field
          current.selections << node
        when Nodes::TypeName, Nodes::ListType, Nodes::NonNullType
          current.type = node
        when Nodes::ListLiteral
          # mutability! 🎉
          current.value = node.values
        when Nodes::InputObject
          current.value = node
        when Nodes::Enum
          current.value = node
        end

        @ast_stack.push(node)
        node
      end

      def end_visit
        removed = @ast_stack.pop
        # p "--> END   #{removed}"
        removed
      end

      # This is for convenience from C
      def add_value(string_value)
        current.value = string_value
      end
    end
  end
end
