<a href="http://arrayfire.com/"><img src="http://arrayfire.com/logos/arrayfire_logo_whitebkgnd.png" width="300"></a>

ArrayFire is a general-purpose library that simplifies the process of developing
software that targets parallel and massively-parallel architectures including
CPUs, GPUs, and other hardware acceleration devices.

# Ruby wrapper for ArrayFire

[![Gitter chat](https://badges.gitter.im/gitterHQ/gitter.png)](https://gitter.im/arrayfire/arrayfire-ruby)

Ruby bindings are a work in progress and are not production ready yet.

## Installation

```sh
git clone https://github.com/arrayfire/arrayfire-rb
cd arrayfire/
gem install bundler
bundle install
rake compile
rspec
```

If you want to try out the code without installing:

```sh
rake pry
```

To install:

```sh
rake install
```

# LICENSE

This software is distributed under the [BSD 3-Clause License](LICENSE).

Copyright © 2017, Prasun Anand and ArrayFire
