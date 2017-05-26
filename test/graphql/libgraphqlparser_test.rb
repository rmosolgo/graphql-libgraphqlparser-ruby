require 'test_helper'

describe GraphQL::Libgraphqlparser do
  def parse(str)
    GraphQL::Libgraphqlparser.parse(str)
  end

  describe "errors" do
    it "raises a parse error in query with null byte" do
      err = assert_raises(GraphQL::ParseError) do
        parse("mutation{\nsend(message: \"null\x00byte\")\n}")
      end
      assert_equal "Invalid null byte in query", err.message
      assert_equal 2, err.line
      assert_equal 20, err.col
    end

    it "raises a parse error in query with null byte and no new line" do
      err = assert_raises(GraphQL::ParseError) do
        parse("mutation{send(message: \"null\x00byte\")}")
      end
      assert_equal "Invalid null byte in query", err.message
      assert_equal 1, err.line
      assert_equal 28, err.col
    end
  end
end
