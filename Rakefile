require 'bundler/setup'
require 'rake/extensiontask'

Bundler::GemHelper.install_tasks

require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test" << "lib"
  t.pattern = "test/**/*_test.rb"
  t.warning = false
end

Rake::ExtensionTask.new "graphql_libgraphqlparser_ext" do |ext|

end

task default: [:clobber, :compile, :test]
