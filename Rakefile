require 'rake'
require 'rake/extensiontask'

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
