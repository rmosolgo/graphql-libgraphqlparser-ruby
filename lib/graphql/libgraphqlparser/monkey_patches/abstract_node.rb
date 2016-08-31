module GraphQL
  module Language
    module Nodes
      class VariableDefinition
        # Make it behave like an Argument
        def value=(new_value)
          @default_value = new_value
        end
      end

      class ListType
        def type=(inner_type)
          self.of_type = inner_type
        end
        def type; self.of_type; end
      end

      class NonNullType
        def type=(inner_type)
          self.of_type = inner_type
        end
        def type; self.of_type; end
      end

      class ListLiteral < AbstractNode
        attr_reader :values

        def initialize
          @values = []
        end

        # This makes it behave like Argument,
        # while it's on the stack it can gobble up values
        def value=(new_value)
          values << new_value
        end
      end
    end
  end
end
