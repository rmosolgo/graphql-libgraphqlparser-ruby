#ifndef Libgraphqlparser_visitor_functions_H
#define Libgraphqlparser_visitor_functions_H

#define VISITOR_CALLBACKS(snake_name, camel_name) \
  int snake_name##_begin_visit(const struct GraphQLAst##camel_name* document, void* builder_ptr); \
  void snake_name##_end_visit(const struct GraphQLAst##camel_name* document, void* builder_ptr); \

void init_visitor_functions();
VISITOR_CALLBACKS(document, Document);
VISITOR_CALLBACKS(operation_definition, OperationDefinition);
VISITOR_CALLBACKS(variable_definition, VariableDefinition);
VISITOR_CALLBACKS(fragment_definition, FragmentDefinition);
VISITOR_CALLBACKS(variable, Variable);
VISITOR_CALLBACKS(field, Field);
VISITOR_CALLBACKS(directive, Directive);
VISITOR_CALLBACKS(argument, Argument);
VISITOR_CALLBACKS(fragment_spread, FragmentSpread);
VISITOR_CALLBACKS(inline_fragment, InlineFragment);
VISITOR_CALLBACKS(list_type, ListType);
VISITOR_CALLBACKS(non_null_type, NonNullType);
VISITOR_CALLBACKS(named_type, NamedType);
VISITOR_CALLBACKS(float_value, FloatValue);
VISITOR_CALLBACKS(int_value, IntValue);
VISITOR_CALLBACKS(boolean_value, BooleanValue);
VISITOR_CALLBACKS(string_value, StringValue);
VISITOR_CALLBACKS(enum_value, EnumValue);
VISITOR_CALLBACKS(list_value, ListValue);
VISITOR_CALLBACKS(object_value, ObjectValue);
VISITOR_CALLBACKS(object_field, ObjectField);

#endif
