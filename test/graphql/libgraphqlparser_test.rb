require 'test_helper'

describe GraphQL::Libgraphqlparser do
  describe '.parse' do
    let(:document) { GraphQL::Libgraphqlparser.parse(query_string) }
    let(:query_string) {%|
        query getStuff($someVar: Int = 1, $anotherVar: String! ) {
          aField @skip(if: true)
          anotherField(someArg: [1,2,3]) {
            nestedField
            ... moreNestedFields
          }
        }

        fragment moreNestedFields on NestedType {
          anotherNestedField
        }
    |}
    it 'parses queries' do
      assert document
    end

    describe "visited nodes" do
      let(:query) { document.parts.first }
      let(:fragment_def) { document.parts.last }

      it "creates a valid document" do
        assert document.is_a?(GraphQL::Language::Nodes::Document)
        assert_equal 2, document.parts.length
      end

      it "creates a valid operation" do
        assert query.is_a?(GraphQL::Language::Nodes::OperationDefinition)
        assert_equal "query", query.operation_type
        assert_equal 2, query.variables.length
        assert_equal 2, query.selections.length
      end

      it "creates a valid fragment" do
        assert fragment_def.is_a?(GraphQL::Language::Nodes::FragmentDefinition)
        assert_equal "NestedType", fragment_def.type
        assert_equal "moreNestedFields", fragment_def.name
        assert_equal 1, fragment_def.selections.length
      end

      it "creates a valid inline fragment"

      it "creates valid variables" do
        query_variable = query.variables.first
        assert_equal "someVar", query_variable.name
        assert_equal "Int", query_variable.type
        # assert_equal "1", query_variable.default_value
      end

      it "creates valid fields"
      it "creates valid arguments"
      it "creates valid fragment spreads"
      it "creates valid directives"
    end
  end
end
