module GraphQL
  module Libgraphqlparser
    # Traverse the parsed tree & build a new tree of
    # GraphQL::Language::Nodes objects
    class ASTVisitor < ::Libgraphqlparser::Visitor
      include GraphQL::Language
      def initialize
        @stack = []
      end

      def document
        @stack.first
      end

      def current_node
        @stack.last
      end

      def push_node(node)
        @stack << node
      end

      def pop_node
        @stack.pop
      end

      def end_visit_with_pop(node)
        pop_node
      end

      def end_visit_without_pop(node)
      end


      def visit_document(node)
        document = Nodes::Document.new(parts: [])
        push_node(document)
      end

      def visit_operation_definition(node)
        op_def = Nodes::OperationDefinition.new(
          operation_type: node.operation,
          name: node.name,
          variables: [],
          directives: [],
          selections: [],
        )
        current_node.parts << op_def
        push_node(op_def)
      end
      alias :end_visit_operation_definition :end_visit_with_pop

      def visit_variable_definition(node)

        var_def = Nodes::Variable.new(
          name: node.variable.name.value,
          type: nil, # node.type,  # name.value,
          default_value: nil, #  node.default_value.value,
        )

        current_node.variables << var_def
        push_node(var_def)
      end
      alias :end_visit_variable_definition :end_visit_with_pop

      def visit_fragment_definition(node)
        frag_def = Nodes::FragmentDefinition.new(
          name: node.name.value,
          type: node.type_condition.name.value,
          selections: [],
          directives: [],
        )
        current_node.parts << frag_def
        push_node(frag_def)
      end
      alias :end_visit_fragment_definition :end_visit_with_pop


      def visit_name(node)
        current_node.name ||= node.value
      end
      alias :end_visit_name :end_visit_without_pop

      def visit_named_type(node)
        current_node.type ||= node.name.value
      end

      alias :end_visit_named_type :end_visit_without_pop

      def method_missing(name, node)
        p name
        # p node
      end
    end
  end
end
