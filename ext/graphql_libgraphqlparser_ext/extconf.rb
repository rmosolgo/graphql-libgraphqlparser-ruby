require 'mkmf'
require 'fileutils'

def build_libgraphql_parser!(libgraphqlparser_path)
  cmake = find_executable 'cmake'

  return false unless cmake

  build_path = File.join(libgraphqlparser_path, 'build')

  Dir.chdir(libgraphqlparser_path) do
    system cmake, "-DCMAKE_INSTALL_PREFIX:PATH=#{build_path}"
    system 'make'
    system 'make all install'
  end

  true
rescue => e
  Logging.message "Could not compile libgraphql, got this error : #{e.inspect}"
  Logging.message "Falling back to local install of libgraphql parser"

  false
end

libgraphqlparser_path = File.join(__dir__, '..', 'libgraphqlparser')

prefixes = if build_libgraphql_parser!(libgraphqlparser_path)
             [File.join(libgraphqlparser_path, 'build')]
           else
             ['/usr', '/usr/local']
           end

if prefix = prefixes.find { |prefix| Dir["#{prefix}/lib/libgraphqlparser*"].first }
  dir_config('graphql', "#{prefix}/include/graphqlparser", "#{prefix}/lib")
else
  dir_config('graphql')
end
abort 'missing libgraphqlparser' unless have_library('graphqlparser')
abort 'missing libgraphqlparser headers' unless have_header('c/GraphQLParser.h')

create_makefile "graphql_libgraphqlparser_ext"
