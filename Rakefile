require "bundler/gem_tasks"
require 'rake'
require 'rake/extensiontask'
require "rake/testtask"
require "rdoc/task"

Rake::ExtensionTask.new do |ext|
  ext.name = 'arrayfire'
  ext.ext_dir = 'ext/mri'
  ext.lib_dir = 'lib/'
  ext.source_pattern = '**/*.{c,cpp, h}'
end

task :console do
  cmd = ['irb', "-r './lib/arrayfire.rb'"]
  run(*cmd)
end

task :pry do
  cmd = ['pry', "-r './lib/arrayfire.rb'"]
  run(*cmd)
end

def run(*cmd)
  sh(cmd.join(' '))
end

RDoc::Task.new do |rdoc|
  rdoc.main = "README.md"
  rdoc.rdoc_files.include(%w{README.md LICENSE CONTRIBUTING.md lib ext})
end

Rake::TestTask.new(:test) do |t|
  t.libs << "test"
  t.libs << "lib"
  t.test_files = FileList['test/**/*_test.rb']
end

task :default => :test
