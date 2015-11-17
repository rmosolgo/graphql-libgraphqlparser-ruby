module GraphQL
  module Language
    module Nodes
      class AbstractNode
        alias :old_initialize :initialize
        # Allow initialize with no args
        def initialize(*args)
          if args.any?
            old_initialize(*args)
          end
        end

        def position
          [line, col]
        end
      end

      # Document = AbstractNode.create(:parts)
      class Document
        def definitions
          @definitions ||= []
        end
      end

      # OperationDefinition = AbstractNode.create(:operation_type, :name, :variables, :directives, :selections)
      class OperationDefinition
        def variables
          @variables ||= []
        end

        def selection_set
          @selection_set ||= []
        end
      end

      # Variable = AbstractNode.create(:name, :type, :default_value)
      VariableDefinition = Variable
      class VariableDefinition
        # Make it behave like an Argument
        def value=(new_value)
          @default_value = new_value
        end
      end

      # VariableIdentifier = AbstractNode.create(:name)

      # FragmentDefinition = AbstractNode.create(:name, :type, :directives, :selections)
      class FragmentDefinition
        def selection_set
          @selection_set ||= []
        end
      end

      # Field = AbstractNode.create(:name, :alias, :arguments, :directives, :selections)
      class Field
        def selection_set
          @selection_set ||= []
        end

        def directives
          @directives ||= []
        end

        def arguments
          @arguments ||= []
        end
      end

      # Directive = AbstractNode.create(:name, :arguments)
      class Directive
        def arguments
          @arguments ||= []
        end
      end

      # FragmentSpread = AbstractNode.create(:name, :directives)
      class FragmentSpread
        def directives
          @directives ||= []
        end
      end

      # InlineFragment = AbstractNode.create(:type, :directives, :selections)
      class InlineFragment
        def directives
          @directives ||= []
        end
        def selection_set
          @selection_set ||= []
        end
      end

      # ListType = AbstractNode.create(:of_type)
      # NonNullType = AbstractNode.create(:of_type)
      # TypeName = AbstractNode.create(:name)
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

      # Argument = AbstractNode.create(:name, :value)
      # Enum = AbstractNode.create(:name)
      class InputObject
        def arguments
          @pairs ||= []
        end
      end

      class ArrayLiteral < AbstractNode
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
