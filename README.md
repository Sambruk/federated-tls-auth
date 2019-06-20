# Sample client code for federated TLS authentication

This repository is a part of the project XYZ financed by NLnet Foundation.

The project is a collaboration between Internetstiftelsen and Sambruk.

The code was developed originally for the EGIL SCIM client, in order to
securely connect to and authenticate a SCIM server, with the help of
authentication metadata from Skolfederation. The code in this repository
however has no dependencies on the EGIL SCIM client and can be re-used in
other projects which need to do the same kind of secure communication.

## Contents

### Tools
In the `tools` directory are scripts that make it easier to fetch, verify
and inspect authentication metadata. For more information, see the
[README](tools/README.md) file in that directory.

### Metadata parsing and authentication example
The `src` directory contains C++ code for interpreting the metadata and
an example program which shows how to use this code, and how it can be used
to connect to and authenticate a server. For more information, see the
[README](src/README.md) file in that directory.
