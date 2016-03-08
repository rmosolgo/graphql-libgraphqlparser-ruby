require 'mkmf'

dir_config('graphql', '/usr/local/include/graphqlparser', '/usr/local/lib')
abort 'missing libgraphqlparser' unless have_library 'graphqlparser'

create_makefile "graphql_libgraphqlparser_ext"
