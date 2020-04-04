# Instructions

These instructions assume that you have fwdpy11 installed, either via `pip3` or via `conda`.

Note that if you've installed via `conda`, you should make sure that `pybind11` has also
been installed by `conda`, else you will be unable to build:

```sh
conda install pybind11
```

You may or may not need `cmake`:

```sh
conda install cmake
```

To build:

```sh
cmake .
make
```

To test:

```sh
python3 test_plugin.py
```

Once this is all working, you can move the CMakeLists.txt and FixedCrossoverInterval.cc files
into your project where you are writing simulations, build there, import, etc., and you'll be
able to use the new type.

# License

The license in GPL3+ because it uses fwdpp code.
