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
```

Run the tests using

```sh
rake test
```

If you want to try out the code without installing:

```sh
rake pry
```

To install:

```sh
rake install
```

# Blog Posts

* [Installation](http://www.prasunanand.com/arrayfire/2017/06/23/gsoc17-arrayfire-ruby-bindings-part-1-installation.html)
* [Af_Array](http://www.prasunanand.com/arrayfire/2017/07/04/gsoc17-arrayfire-ruby-bindings-part-2-af_array.html)
* [Test Suite and Algorithm class](http://www.prasunanand.com/arrayfire/2017/07/22/gsoc17-arrayfire-ruby-bindings-part-3-minitest-algorithm.html)
* [BLAS and LAPACK routines](http://www.prasunanand.com/arrayfire/2017/08/16/gsoc17-arrayfire-ruby-bindings-part-4-blas-lapack.html)
* [Statistics and Random enngine routines](http://www.prasunanand.com/arrayfire/2017/08/17/gsoc17-arrayfire-ruby-bindings-part-4-statistics-and-random-engine.html)
* [Device and Util class](http://www.prasunanand.com/arrayfire/2017/08/22/gsoc17-arrayfire-ruby-bindings-part-6-device.html)
* [Multiple Backends: CUDA, OpenCL and CPU](http://www.prasunanand.com/arrayfire/2017/08/24/gsoc17-arrayfire-ruby-bindings-part-7-backend-cuda-and-opencl.html)
* [Interfacing to NMatrix](http://www.prasunanand.com/arrayfire/2017/08/24/gsoc17-arrayfire-ruby-bindings-part-8-nmatrix-interface.html)

# Contributing

For details see [CONTRIBUTING](CONTRIBUTING.md).

# Acknowledgements

* Google and the Ruby Science Foundation for the [Google Summer of Code 2017 grant](https://summerofcode.withgoogle.com/projects/#5070443972132864). Special Thanks to [Pjotr Prins](https://github.com/pjotrp/), [Sameer Deshmukh](https://github.com/v0dro) and [Pradeep Garigipati](https://github.com/9prady9/).

# LICENSE

This software is distributed under the [BSD 3-Clause License](LICENSE).

Copyright © 2017, Prasun Anand and ArrayFire
