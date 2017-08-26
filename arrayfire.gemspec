# coding: utf-8
$:.unshift File.expand_path("../lib", __FILE__)

require 'arrayfire/version.rb'

ArrayFire::DESCRIPTION = <<MSG
ArrayFire is a general-purpose library that simplifies the process of developing
software that targets parallel and massively-parallel architectures including
CPUs, GPUs, and other hardware acceleration devices.
MSG

Gem::Specification.new do |gem|
  gem.name        = 'arrayfire'
  gem.version     = ArrayFire::VERSION
  gem.date        = '2016-09-29'
  gem.summary     = 'Ruby wrapper for ArrayFire.'
  gem.description = ArrayFire::DESCRIPTION
  gem.authors     = ['Prasun Anand']
  gem.email       = 'prasunanand.bitsp@gmail.com'
  gem.files       = ['lib/arrayfire.rb']
  gem.homepage    = 'http://rubygems.org/gems/arrayfire'
  gem.license     = 'BSD-3-Clause'
  gem.extensions  = ['ext/mri/extconf.rb']
  gem.files       = `git ls-files -- ext/mri`.split("\n")
  gem.files      += `git ls-files -- lib`.split("\n")
  gem.require_paths = ["lib"]
  gem.add_development_dependency 'rubocop', '~> 0'
  gem.add_development_dependency 'bundler', '~>1.6'
  gem.add_development_dependency 'json', '~> 0'
  gem.add_development_dependency 'pry', '~>0.10'
  gem.add_development_dependency 'rake', '~>10.3'
  gem.add_development_dependency 'rake-compiler', '~>0.8'
  gem.add_development_dependency 'rdoc', '~>4.0', '>=4.0.1'
  gem.add_development_dependency "minitest", "~> 5.0"

  gem.add_development_dependency 'nmatrix', '~> 0.2.1'
end