# library-gcc

This project includes the latest distribution of googletest, a subset of boost, and a distribution of ftplibpp.

# Building

If you already have the latest version of GoogleTest installed, you can update the CMakeLists.txt file in ./libraryTest to properly reference it (or an env variable). Or you can choose to build the included distribution of GoogleTest. One way to build it:

    cd googletest
    cmake .
    make

Build ftplibpp in library-gcc:

    cd ftplibpp
    make
   
You can specify a path for 3rd party dependencies using the `EXT_PREFIX` variable. By
default this is set to `/usr/local`. For example

    # use 3rd party libraries installed in /opt/local
    EXT_PREFIX=/opt/local make

If you receive an error about openssl/ssh.h not being found:

    sudo apt-get install libssl-dev

You will likely receive some warnings when building ftplibpp.

Run the bash script that builds and executes the tests:

    ./test

You should see well over 100 tests that are passing (green).
