require 'mkmf'

prefixes = %w(/usr /usr/local)
if prefix = prefixes.find{ |candidate| Dir["#{candidate}/lib/libgraphqlparser*"].first }
  dir_config('graphqlparser', "#{prefix}/include/graphqlparser", "#{prefix}/lib")
else
  dir_config('graphqlparser')
end

abort 'missing libgraphqlparser' unless have_library('graphqlparser')
abort 'missing libgraphqlparser headers' unless have_header('c/GraphQLParser.h')

create_makefile "graphql_libgraphqlparser_ext"
