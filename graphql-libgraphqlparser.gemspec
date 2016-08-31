lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'graphql/libgraphqlparser/version'

Gem::Specification.new do |spec|
  spec.name          = 'graphql-libgraphqlparser'
  spec.version       = GraphQL::Libgraphqlparser::VERSION
  spec.authors       = ['Robert Mosolgo']
  spec.homepage      = 'https://github.com/rmosolgo/graphql-libgraphqlparser-ruby'
  spec.email         = ['rdmosolgo@gmail.com']
  spec.summary       = "Use Libgraphqlparser to parse queries for the GraphQL gem"
  spec.license       = "minitest"

  spec.extensions    = ['ext/graphql_libgraphqlparser_ext/extconf.rb']
  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ['lib']

  spec.add_runtime_dependency 'graphql', '~> 0.11'

  spec.add_development_dependency 'bundler', '~> 1.0'
  spec.add_development_dependency "guard", "~> 2.12"
  spec.add_development_dependency "guard-bundler", "~> 2.1"
  spec.add_development_dependency "guard-minitest", "~> 2.4"
  spec.add_development_dependency "guard-rake", "~> 1.0"
  # Lock to a lower version to support Ruby 2.1
  spec.add_development_dependency "listen", "~> 3.0.0"
  spec.add_development_dependency 'minitest', '~> 5.8'
  spec.add_development_dependency "minitest-reporters", "~>1.0"
  spec.add_development_dependency 'rake', '~> 11.0'
  spec.add_development_dependency 'rake-compiler', '~> 0.9'
end
