#include "graphql_libgraphqlparser_ext.h"

// Get the name from `node` using `get_name_fn`,
// then assign it to `rb_node` with `#name=`
#define ASSIGN_NAME(rb_node, node, get_name_fn) \
  rb_funcall(rb_node, name_set_intern, 1,       \
    rb_str_new2(                                \
      GraphQLAstName_get_value(                 \
          get_name_fn(node)                     \
        )                                       \
      )                                         \
    );                                          \

VALUE type_set_intern, name_set_intern, add_value_intern, end_visit_intern, begin_visit_intern, line_set_intern, col_set_intern;
int rb_utf_8_enc;

// Get the line & column from `node` and assign it to `rb_node`
inline void set_node_location(const struct GraphQLAstNode *node, VALUE rb_node) {
  struct GraphQLAstLocation location = {0};
  graphql_node_get_location(node, &location);
  rb_funcall(rb_node, line_set_intern, 1, INT2NUM(location.beginLine));
  rb_funcall(rb_node, col_set_intern, 1, INT2NUM(location.beginColumn));
}

// Call the finalizer method on `builder_ptr`
inline void end_visit(void * builder_ptr) {
  rb_funcall(
    (VALUE) builder_ptr,
    end_visit_intern,
    0
  );
}

// Build a Ruby node named `node_name_string` out of `node` and return it
inline VALUE build_rb_node(struct GraphQLAstNode* node, char* node_name_string, void* builder_ptr) {
  VALUE rb_node = rb_funcall(
      (VALUE) builder_ptr,
      begin_visit_intern,
      1,
      rb_str_new2(node_name_string)
    );
  set_node_location(node, rb_node);
  return rb_node;
}

// Send `rb_literal_value` to the current node's `#value=` method
inline void assign_literal_value(VALUE rb_literal_value, void* builder_ptr) {
  rb_funcall(
      (VALUE) builder_ptr,
      add_value_intern,
      1,
      rb_literal_value
  );
}

// Prepare a bunch of global Ruby method IDs
void init_visitor_functions() {
  type_set_intern = rb_intern("type=");
  name_set_intern = rb_intern("name=");
  add_value_intern = rb_intern("add_value");
  end_visit_intern = rb_intern("end_visit");
  begin_visit_intern = rb_intern("begin_visit");
  line_set_intern = rb_intern("line=");
  col_set_intern = rb_intern("col=");
  rb_utf_8_enc = rb_enc_find_index("UTF-8");
}

// There's a `begin_visit` and `end_visit` for each node.
// Some of the end_visit callbacks are empty but that's ok,
// It lets us use macros in the other files.

int document_begin_visit(const struct GraphQLAstDocument* node, void* builder_ptr) {
  build_rb_node((struct GraphQLAstNode*) node, "Document", builder_ptr);
  return 1;
}

void document_end_visit(const struct GraphQLAstDocument* node, void* builder_ptr) {
}

int operation_definition_begin_visit(const struct GraphQLAstOperationDefinition* node, void* builder_ptr) {
  const struct GraphQLAstName* ast_operation_name;
  const char* operation_type;
  VALUE operation_type_str, rb_node;

  rb_node = build_rb_node((struct GraphQLAstNode*) node, "OperationDefinition", builder_ptr);

  ast_operation_name = GraphQLAstOperationDefinition_get_name(node);
  if (ast_operation_name) {
    const char* operation_name = GraphQLAstName_get_value(ast_operation_name);
    rb_funcall(rb_node, name_set_intern, 1, rb_str_new2(operation_name));
  }

  operation_type = GraphQLAstOperationDefinition_get_operation(node);

  if (operation_type) {
    operation_type_str = rb_str_new2(operation_type);
  } else {
    operation_type_str = rb_str_new2("query");
  }

  rb_funcall(rb_node, rb_intern("operation_type="), 1, operation_type_str);

  return 1;
}

void operation_definition_end_visit(const struct GraphQLAstOperationDefinition* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int variable_definition_begin_visit(const struct GraphQLAstVariableDefinition* node, void* builder_ptr) {
  build_rb_node((struct GraphQLAstNode*) node, "VariableDefinition", builder_ptr);
  return 1;
}

void variable_definition_end_visit(const struct GraphQLAstVariableDefinition* node, void* builder_ptr) {
  end_visit(builder_ptr);
}


int fragment_definition_begin_visit(const struct GraphQLAstFragmentDefinition* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "FragmentDefinition", builder_ptr);
  ASSIGN_NAME(rb_node, node, GraphQLAstFragmentDefinition_get_name)
  return 1;
}

void fragment_definition_end_visit(const struct GraphQLAstFragmentDefinition* node, void* builder_ptr) {
  end_visit(builder_ptr);
}


int variable_begin_visit(const struct GraphQLAstVariable* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "VariableIdentifier", builder_ptr);
  // This might actually assign the name of a VariableDefinition:
  ASSIGN_NAME(rb_node, node, GraphQLAstVariable_get_name)
  return 1;
}

void variable_end_visit(const struct GraphQLAstVariable* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int field_begin_visit(const struct GraphQLAstField* node, void* builder_ptr) {
  const struct GraphQLAstName* ast_field_alias;
  const char* str_field_alias;
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "Field", builder_ptr);

  ASSIGN_NAME(rb_node, node, GraphQLAstField_get_name)

  ast_field_alias = GraphQLAstField_get_alias(node);
  if (ast_field_alias) {
    str_field_alias = GraphQLAstName_get_value(ast_field_alias);
    rb_funcall(rb_node, rb_intern("alias="), 1, rb_str_new2(str_field_alias));
  }
  return 1;
}

void field_end_visit(const struct GraphQLAstField* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int directive_begin_visit(const struct GraphQLAstDirective* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "Directive", builder_ptr);

  ASSIGN_NAME(rb_node, node, GraphQLAstDirective_get_name)
  return 1;
}

void directive_end_visit(const struct GraphQLAstDirective* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int argument_begin_visit(const struct GraphQLAstArgument* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "Argument", builder_ptr);
  ASSIGN_NAME(rb_node, node, GraphQLAstArgument_get_name)
  return 1;
}

void argument_end_visit(const struct GraphQLAstArgument* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int fragment_spread_begin_visit(const struct GraphQLAstFragmentSpread* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "FragmentSpread", builder_ptr);
  ASSIGN_NAME(rb_node, node, GraphQLAstFragmentSpread_get_name)
  return 1;
}

void fragment_spread_end_visit(const struct GraphQLAstFragmentSpread* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int inline_fragment_begin_visit(const struct GraphQLAstInlineFragment* node, void* builder_ptr) {
  build_rb_node((struct GraphQLAstNode*) node, "InlineFragment", builder_ptr);
  return 1;
}

void inline_fragment_end_visit(const struct GraphQLAstInlineFragment* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int list_type_begin_visit(const struct GraphQLAstListType* node, void* builder_ptr) {
  build_rb_node((struct GraphQLAstNode*) node, "ListType", builder_ptr);
  return 1;
}

void list_type_end_visit(const struct GraphQLAstListType* node, void* builder_ptr) {
  end_visit(builder_ptr);
}


int non_null_type_begin_visit(const struct GraphQLAstNonNullType* node, void* builder_ptr) {
  build_rb_node((struct GraphQLAstNode*) node, "NonNullType", builder_ptr);
  return 1;
}

void non_null_type_end_visit(const struct GraphQLAstNonNullType* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int named_type_begin_visit(const struct GraphQLAstNamedType* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "TypeName", builder_ptr);
  ASSIGN_NAME(rb_node, node, GraphQLAstNamedType_get_name)
  return 1;
}

void named_type_end_visit(const struct GraphQLAstNamedType* node, void* builder_ptr) {
  end_visit(builder_ptr);
}


int float_value_begin_visit(const struct GraphQLAstFloatValue* node, void* builder_ptr) {
  const char* str_float = GraphQLAstFloatValue_get_value(node);
  VALUE rb_float = rb_funcall(rb_str_new2(str_float), rb_intern("to_f"), 0);
  assign_literal_value(rb_float, builder_ptr);
  return 1;
}

void float_value_end_visit(const struct GraphQLAstFloatValue* node, void* builder_ptr) {
}

int int_value_begin_visit(const struct GraphQLAstIntValue* node, void* builder_ptr) {
  const char* str_int = GraphQLAstIntValue_get_value(node);
  VALUE rb_int = rb_funcall(rb_str_new2(str_int), rb_intern("to_i"), 0);
  assign_literal_value(rb_int, builder_ptr);
  return 1;
}

void int_value_end_visit(const struct GraphQLAstIntValue* node, void* builder_ptr) {
}

int boolean_value_begin_visit(const struct GraphQLAstBooleanValue* node, void* builder_ptr) {
  const int bool_value = GraphQLAstBooleanValue_get_value(node);
  VALUE rb_bool = bool_value ? Qtrue : Qfalse;
  assign_literal_value(rb_bool, builder_ptr);

  return 1;
}

void boolean_value_end_visit(const struct GraphQLAstBooleanValue* node, void* builder_ptr) {
}

int string_value_begin_visit(const struct GraphQLAstStringValue* node, void* builder_ptr) {
  const char* str_value = GraphQLAstStringValue_get_value(node);
  VALUE rb_string = rb_str_new2(str_value);
  rb_enc_associate_index(rb_string, rb_utf_8_enc);
  assign_literal_value(rb_string, builder_ptr);
  return 1;
}

void string_value_end_visit(const struct GraphQLAstStringValue* node, void* builder_ptr) {
}

int enum_value_begin_visit(const struct GraphQLAstEnumValue* node, void* builder_ptr) {
  const char* str_value;
  VALUE rb_string;
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "Enum", builder_ptr);
  str_value = GraphQLAstEnumValue_get_value(node);
  rb_string = rb_str_new2(str_value);
  rb_enc_associate_index(rb_string, rb_utf_8_enc);
  rb_funcall(rb_node, name_set_intern, 1, rb_string);
  return 1;
}

void enum_value_end_visit(const struct GraphQLAstEnumValue* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int list_value_begin_visit(const struct GraphQLAstListValue* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "ListLiteral", builder_ptr);
  return 1;
}

void list_value_end_visit(const struct GraphQLAstListValue* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int object_value_begin_visit(const struct GraphQLAstObjectValue* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "InputObject", builder_ptr);
  return 1;
}

void object_value_end_visit(const struct GraphQLAstObjectValue* node, void* builder_ptr) {
  end_visit(builder_ptr);
}

int object_field_begin_visit(const struct GraphQLAstObjectField* node, void* builder_ptr) {
  VALUE rb_node = build_rb_node((struct GraphQLAstNode*) node, "Argument", builder_ptr);
  ASSIGN_NAME(rb_node, node, GraphQLAstObjectField_get_name)
  return 1;
}

void object_field_end_visit(const struct GraphQLAstObjectField* node, void* builder_ptr) {
  end_visit(builder_ptr);
}
