#include "graphql_libgraphqlparser_ext.h"
#include "visitor_functions.h"

#define ATTACH_CALLBACKS(node_name)                                         \
  Libgraphqlparser_Callbacks.visit_##node_name = node_name##_begin_visit;   \
  Libgraphqlparser_Callbacks.end_visit_##node_name = node_name##_end_visit; \

VALUE Libgraphqlparser_ParseError;
VALUE Libgraphqlparser_Builder;

static struct GraphQLAstVisitorCallbacks Libgraphqlparser_Callbacks;

// Given a Ruby querystring, return a
// GraphQL::Nodes::Document instance.
VALUE GraphQL_Libgraphqlparser_parse(VALUE self, VALUE query_string) {
  const char* c_query_string = StringValueCStr(query_string);
  const char* parse_error_message;
  VALUE exception;
  VALUE builder = Qnil;

  struct GraphQLAstNode *parse_result = graphql_parse_string(c_query_string, &parse_error_message);

  if (parse_result == NULL) {
    exception = rb_exc_new_cstr(Libgraphqlparser_ParseError, parse_error_message);
    graphql_error_free(parse_error_message);
    rb_exc_raise(exception);
  } else {
    builder = rb_class_new_instance(0, NULL, Libgraphqlparser_Builder);
    graphql_node_visit(parse_result, &Libgraphqlparser_Callbacks, (void*)builder);
  }

  return builder;
}

// Initialize the extension
void Init_graphql_libgraphqlparser_ext() {
  VALUE GraphQL = rb_define_module("GraphQL");
  VALUE Libgraphqlparser = rb_define_module_under(GraphQL, "Libgraphqlparser");
  rb_define_singleton_method(Libgraphqlparser, "builder_parse", GraphQL_Libgraphqlparser_parse, 1);

  Libgraphqlparser_ParseError = rb_define_class_under(Libgraphqlparser, "ParseError", rb_eStandardError);
  Libgraphqlparser_Builder = rb_const_get(Libgraphqlparser, rb_intern("Builder"));

  init_visitor_functions();
  // Attach the functions to the Callbacks struct
  ATTACH_CALLBACKS(document);
  ATTACH_CALLBACKS(operation_definition);
  ATTACH_CALLBACKS(variable_definition);
  ATTACH_CALLBACKS(fragment_definition);
  ATTACH_CALLBACKS(variable);
  ATTACH_CALLBACKS(field);
  ATTACH_CALLBACKS(directive);
  ATTACH_CALLBACKS(argument);
  ATTACH_CALLBACKS(fragment_spread);
  ATTACH_CALLBACKS(inline_fragment);
  ATTACH_CALLBACKS(list_type);
  ATTACH_CALLBACKS(non_null_type);
  ATTACH_CALLBACKS(named_type);
  ATTACH_CALLBACKS(float_value);
  ATTACH_CALLBACKS(int_value);
  ATTACH_CALLBACKS(boolean_value);
  ATTACH_CALLBACKS(string_value);
  ATTACH_CALLBACKS(enum_value);
  ATTACH_CALLBACKS(array_value);
  ATTACH_CALLBACKS(object_value);
  ATTACH_CALLBACKS(object_field);
}
