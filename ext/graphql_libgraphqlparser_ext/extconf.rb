require 'mkmf'

prefixes = %w(/usr /usr/local)
if prefix = prefixes.find{ |candidate| Dir["#{candidate}/lib/libgraphqlparser*"].first }
  # This is unorthodox usage of dir_config. The problem is that libgraphqlparser installs its header
  # files to a subdirectory of include/, so to find them we have to specify a custom "default" location
  # which is relative to the guessed location of the install. In other words, not a "default" at all.
  dir_config('graphqlparser', "#{prefix}/include/graphqlparser", "#{prefix}/lib")
else
  # Failing that, fallback to defaults (/include and /lib)
  dir_config('graphqlparser')
end

LIBRARY_MISSING_ERROR_MESSAGE = <<-EOT

🚨 Could not find libgraphqlparser library. Have you installed it? 🚨
  See: https://github.com/rmosolgo/graphql-libgraphqlparser-ruby#installation

EOT

HEADER_MISSING_ERROR_MESSAGE = <<-EOT

🚨 Could not find libgraphqlparser headers. Is your library installed in a custom location? 🚨
  See: https://github.com/rmosolgo/graphql-libgraphqlparser-ruby#overriding-the-location-of-libgraphqlparser

EOT

abort LIBRARY_MISSING_ERROR_MESSAGE unless have_library('graphqlparser')
abort HEADER_MISSING_ERROR_MESSAGE unless have_header('c/GraphQLParser.h')

create_makefile "graphql_libgraphqlparser_ext"
