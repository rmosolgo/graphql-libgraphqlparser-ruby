#ifndef Libgraphqlparser_visitor_functions_C
#define Libgraphqlparser_visitor_functions_C

#include "c/GraphQLAst.h"
#include "c/GraphQLAstNode.h"
#include <ruby.h>
#include <ruby/encoding.h>

// These macros are a bit janky,
// they depend on the function signature
// being the same all the time: `(GraphQLAstNode* node, void* builder_ptr)`.
//
// Then they provide `rb_node` that you can work on in the function body.
#define BEGIN(node_name_string)                           \
  VALUE rb_node = rb_funcall((VALUE) builder_ptr, rb_intern("begin_visit"), 1, rb_str_new2(node_name_string));   \
  ADD_LOCATION_INFO                                       \

#define END                                                   \
  rb_funcall((VALUE) builder_ptr, rb_intern("end_visit"), 0); \

#define ADD_LITERAL(rb_value)                                           \
  rb_funcall((VALUE) builder_ptr, rb_intern("add_value"), 1, rb_value); \

#define ADD_LOCATION_INFO        \
  struct GraphQLAstLocation* location = malloc(sizeof(struct GraphQLAstLocation)); \
  graphql_node_get_location((struct GraphQLAstNode *)node, location);            \
  rb_funcall(rb_node, rb_intern("line="), 1, INT2NUM(location->beginLine)); \
  rb_funcall(rb_node, rb_intern("col="), 1, INT2NUM(location->beginColumn)); \
  free(location); \

#define ASSIGN_NAME(get_name_fn)              \
  rb_funcall(rb_node, rb_intern("name="), 1,  \
    rb_str_new2(                              \
      GraphQLAstName_get_value(               \
          get_name_fn(node)                   \
        )                                     \
      )                                       \
    );                                        \

// There's a `begin_visit` and `end_visit` for each node.
// Some of the end_visit callbacks are empty but that's ok,
// It lets us use macros in the other files.

int document_begin_visit(const struct GraphQLAstDocument* node, void* builder_ptr) {
  BEGIN("Document")

  return 1;
}

void document_end_visit(const struct GraphQLAstDocument* node, void* builder_ptr) {
}

int operation_definition_begin_visit(const struct GraphQLAstOperationDefinition* node, void* builder_ptr) {
  BEGIN("OperationDefinition")

  const struct GraphQLAstName* ast_operation_name = GraphQLAstOperationDefinition_get_name(node);
  if (ast_operation_name) {
    const char* operation_name = GraphQLAstName_get_value(ast_operation_name);
    rb_funcall(rb_node, rb_intern("name="), 1, rb_str_new2(operation_name));
  }

  const char* operation_type = GraphQLAstOperationDefinition_get_operation(node);

  VALUE operation_type_str;
  if (operation_type) {
    operation_type_str = rb_str_new2(operation_type);
  } else {
    operation_type_str = rb_str_new2("query");
  }

  rb_funcall(rb_node, rb_intern("operation_type="), 1, operation_type_str);

  return 1;
}

void operation_definition_end_visit(const struct GraphQLAstOperationDefinition* node, void* builder_ptr) {
  END
}

int variable_definition_begin_visit(const struct GraphQLAstVariableDefinition* node, void* builder_ptr) {
  BEGIN("VariableDefinition")
  return 1;
}

void variable_definition_end_visit(const struct GraphQLAstVariableDefinition* node, void* builder_ptr) {
  END
}


int fragment_definition_begin_visit(const struct GraphQLAstFragmentDefinition* node, void* builder_ptr) {
  BEGIN("FragmentDefinition")
  ASSIGN_NAME(GraphQLAstFragmentDefinition_get_name)

  const struct GraphQLAstNamedType* ast_named_type = GraphQLAstFragmentDefinition_get_type_condition(node);
  const struct GraphQLAstName* ast_named_type_ast_name = GraphQLAstNamedType_get_name(ast_named_type);
  const char* ast_named_type_str_name = GraphQLAstName_get_value(ast_named_type_ast_name);
  rb_funcall(rb_node, rb_intern("type="), 1, rb_str_new2(ast_named_type_str_name));

  return 1;
}

void fragment_definition_end_visit(const struct GraphQLAstFragmentDefinition* node, void* builder_ptr) {
  END
}


int variable_begin_visit(const struct GraphQLAstVariable* node, void* builder_ptr) {
  BEGIN("VariableIdentifier")
  // This might actually assign the name of a VariableDefinition:
  ASSIGN_NAME(GraphQLAstVariable_get_name)

  return 1;
}

void variable_end_visit(const struct GraphQLAstVariable* node, void* builder_ptr) {
  END
}

int field_begin_visit(const struct GraphQLAstField* node, void* builder_ptr) {
  BEGIN("Field")
  ASSIGN_NAME(GraphQLAstField_get_name)

  const struct GraphQLAstName* ast_field_alias = GraphQLAstField_get_alias(node);
  if (ast_field_alias) {
    const char* str_field_alias = GraphQLAstName_get_value(ast_field_alias);
    rb_funcall(rb_node, rb_intern("alias="), 1, rb_str_new2(str_field_alias));
  }

  return 1;
}

void field_end_visit(const struct GraphQLAstField* node, void* builder_ptr) {
  END
}

int directive_begin_visit(const struct GraphQLAstDirective* node, void* builder_ptr) {
  BEGIN("Directive")
  ASSIGN_NAME(GraphQLAstDirective_get_name)

  return 1;
}

void directive_end_visit(const struct GraphQLAstDirective* node, void* builder_ptr) {
  END
}

int argument_begin_visit(const struct GraphQLAstArgument* node, void* builder_ptr) {
  BEGIN("Argument")
  ASSIGN_NAME(GraphQLAstArgument_get_name)

  return 1;
}

void argument_end_visit(const struct GraphQLAstArgument* node, void* builder_ptr) {
  END
}

int fragment_spread_begin_visit(const struct GraphQLAstFragmentSpread* node, void* builder_ptr) {
  BEGIN("FragmentSpread")
  ASSIGN_NAME(GraphQLAstFragmentSpread_get_name)

  return 1;
}

void fragment_spread_end_visit(const struct GraphQLAstFragmentSpread* node, void* builder_ptr) {
  END
}

int inline_fragment_begin_visit(const struct GraphQLAstInlineFragment* node, void* builder_ptr) {
  BEGIN("InlineFragment")

  const struct GraphQLAstNamedType* ast_named_type = GraphQLAstInlineFragment_get_type_condition(node);
  const struct GraphQLAstName* ast_named_type_ast_name = GraphQLAstNamedType_get_name(ast_named_type);
  const char* ast_named_type_str_name = GraphQLAstName_get_value(ast_named_type_ast_name);
  rb_funcall(rb_node, rb_intern("type="), 1, rb_str_new2(ast_named_type_str_name));

  return 1;
}

void inline_fragment_end_visit(const struct GraphQLAstInlineFragment* node, void* builder_ptr) {
  END
}

int list_type_begin_visit(const struct GraphQLAstListType* node, void* builder_ptr) {
  BEGIN("ListType")
  return 1;
}

void list_type_end_visit(const struct GraphQLAstListType* node, void* builder_ptr) {
  END
}


int non_null_type_begin_visit(const struct GraphQLAstNonNullType* node, void* builder_ptr) {
  BEGIN("NonNullType")
  return 1;
}

void non_null_type_end_visit(const struct GraphQLAstNonNullType* node, void* builder_ptr) {
  END
}

int named_type_begin_visit(const struct GraphQLAstNamedType* node, void* builder_ptr) {
  BEGIN("TypeName")
  ASSIGN_NAME(GraphQLAstNamedType_get_name)

  return 1;
}

void named_type_end_visit(const struct GraphQLAstNamedType* node, void* builder_ptr) {
  END
}


int float_value_begin_visit(const struct GraphQLAstFloatValue* node, void* builder_ptr) {
  const char* str_float = GraphQLAstFloatValue_get_value(node);
  VALUE rb_float = rb_funcall(rb_str_new2(str_float), rb_intern("to_f"), 0);
  ADD_LITERAL(rb_float);
  return 1;
}

void float_value_end_visit(const struct GraphQLAstFloatValue* node, void* builder_ptr) {
}

int int_value_begin_visit(const struct GraphQLAstIntValue* node, void* builder_ptr) {
  const char* str_int = GraphQLAstIntValue_get_value(node);
  VALUE rb_int = rb_funcall(rb_str_new2(str_int), rb_intern("to_i"), 0);
  ADD_LITERAL(rb_int);
  return 1;
}

void int_value_end_visit(const struct GraphQLAstIntValue* node, void* builder_ptr) {
}

int boolean_value_begin_visit(const struct GraphQLAstBooleanValue* node, void* builder_ptr) {
  const int bool_value = GraphQLAstBooleanValue_get_value(node);
  if (bool_value) {
    ADD_LITERAL(Qtrue)
  } else {
    ADD_LITERAL(Qfalse)
  }
  return 1;
}

void boolean_value_end_visit(const struct GraphQLAstBooleanValue* node, void* builder_ptr) {
}

int string_value_begin_visit(const struct GraphQLAstStringValue* node, void* builder_ptr) {
  const char* str_value = GraphQLAstStringValue_get_value(node);
  VALUE rb_string = rb_str_new2(str_value);
  int enc = rb_enc_find_index("UTF-8");
  rb_enc_associate_index(rb_string, enc);
  ADD_LITERAL(rb_string);
  return 1;
}

void string_value_end_visit(const struct GraphQLAstStringValue* node, void* builder_ptr) {
}

int enum_value_begin_visit(const struct GraphQLAstEnumValue* node, void* builder_ptr) {
  const char* str_value = GraphQLAstEnumValue_get_value(node);
  VALUE rb_string = rb_str_new2(str_value);
  int enc = rb_enc_find_index("UTF-8");
  rb_enc_associate_index(rb_string, enc);
  ADD_LITERAL(rb_string);
  return 1;
}

void enum_value_end_visit(const struct GraphQLAstEnumValue* node, void* builder_ptr) {
}

int array_value_begin_visit(const struct GraphQLAstArrayValue* node, void* builder_ptr) {
  BEGIN("ArrayLiteral")
  return 1;
}

void array_value_end_visit(const struct GraphQLAstArrayValue* node, void* builder_ptr) {
  END
}

int object_value_begin_visit(const struct GraphQLAstObjectValue* node, void* builder_ptr) {
  BEGIN("InputObject")
  return 1;
}

void object_value_end_visit(const struct GraphQLAstObjectValue* node, void* builder_ptr) {
  END
}

int object_field_begin_visit(const struct GraphQLAstObjectField* node, void* builder_ptr) {
  BEGIN("Argument")
  ASSIGN_NAME(GraphQLAstObjectField_get_name)
  return 1;
}

void object_field_end_visit(const struct GraphQLAstObjectField* node, void* builder_ptr) {
  END
}

#endif
