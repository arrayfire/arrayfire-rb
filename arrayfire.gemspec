Gem::Specification.new do |gem|
  gem.name        = 'arrayfire'
  gem.version     = '0.0.0'
  gem.date        = '2016-09-29'
  gem.summary     = 'Ruby wrapper for ArrayFire.'
  gem.description = 'Ruby wrapper for ArrayFire.'
  gem.authors     = ['Prasun Anand']
  gem.email       = 'prasunanand.bitsp@gmail.com'
  gem.files       = ['lib/arrayfire.rb']
  gem.homepage    = 'http://rubygems.org/gems/arrayfire'
  gem.license     = 'BSD-3-Clause'
  gem.extensions  = ['ext/mri/extconf.rb']
  gem.files       = `git ls-files -- ext/mri`.split("\n")
  gem.files      += `git ls-files -- lib`.split("\n")
  gem.require_paths = ["lib"]
  gem.add_development_dependency 'rubocop'
  gem.add_development_dependency 'bundler', '~>1.6'
  gem.add_development_dependency 'json'
  gem.add_development_dependency 'pry', '~>0.10'
  gem.add_development_dependency 'rake', '~>10.3'
  gem.add_development_dependency 'rake-compiler', '~>0.8'
  gem.add_development_dependency 'rdoc', '~>4.0', '>=4.0.1'
  gem.add_development_dependency "minitest", "~> 5.0"
end