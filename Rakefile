require 'bundler/setup'
require 'rake/extensiontask'

Bundler::GemHelper.install_tasks

require 'rake/testtask'

Rake::TestTask.new do |t|
  t.libs << "test" << "lib"
  t.pattern = "test/**/*_test.rb"
end

Rake::ExtensionTask.new "libgraphqlparser" do |ext|
  ext.lib_dir = "lib/graphql/libgraphqlparser"
end

task default: [:clobber, :compile, :test]
