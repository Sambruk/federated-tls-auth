# A module for using metadata

This directory contains C++ code for parsing and using the contents in a
metadata file, for connecting to and authenticating a server.

`fedtlsauth` contains re-usable code suitable for a C++ client that
wishes to connect and authenticate an entity from a metadata file.

The file `get.cpp` contains a small example program which uses the
code in fedtlsauth in order to do a secure GET request over HTTPS.

# Dependencies

The re-usable code in `fedtlsauth` uses the Boost C++ libraries. If you only
wish to use the code in `fedtlsauth` it is enough to have the Boost headers
available.

The example program depends on libcurl and the Boost library program_options.

# Building the example program

First make sure the following dependencies are installed:

* Boost (the whole installation, or just headers and libboost_program_options)
* libcurl

Then go to the `src` directory and run `make`

# Running the example program

Here's an example of running the program in order to get the resource
`ServiceProviderConfig` from the server named  `prod` owned by
entity `example.org`:

```
./get --metadata /home/joe/git/EgilSCIM/tools/metadata.txt \
      --entity example.org \
      --server prod \
      --cert my.client.cert.pem \
      --key my.private.key.pem \
      --path ServiceProviderConfig
```
If the client can connect and authenticate successfully, and get the provided
resource, the reply from the server will be printed to standard output.
