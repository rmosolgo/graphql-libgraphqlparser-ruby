guard :bundler do
  watch('Gemfile')
  # Uncomment next line if your Gemfile contains the `gemspec' command.
  watch(/^.+\.gemspec/)
end

guard :minitest do
  watch(%r{^test/(.*)_test\.rb})
  watch(%r{^lib/(.+)\.rb})          { |m| "test/#{m[1]}_test.rb" }
  watch(%r{^test/test_helper\.rb})  { 'test' }
  watch(%r{^test/support/.*\.rb})   { 'test' }
end
