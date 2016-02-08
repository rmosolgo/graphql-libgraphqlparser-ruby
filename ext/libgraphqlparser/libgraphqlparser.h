#ifndef Libgraphqlparser_EXT_H
#define Libgraphqlparser_EXT_H

#include <ruby.h>
#include <ruby/encoding.h>
#include <c/GraphQLParser.h>
#include <c/GraphQLAstNode.h>
#include <c/GraphQLAstVisitor.h>
#include <c/GraphQLAst.h>

void Init_libgraphqlparser(void);

#endif
