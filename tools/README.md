# Tools to simplify working with the metadata

This directory is for tools that may simplify usage of a
client which uses the metadata for federated TLS authentication.

All tools can be run with the -h flag to show a brief description
of how to run the tool.

## fetch_metadata
The script fetch_metadata.py will both download and verify the authentication
metadata against a key. The decoded metadata can then be used by a client or
server in order to connect to and authenticate a peer.

Before running the script you need to make sure that Python 3 and the
python-jose package is installed.

For instance, to install on Debian these commands can be used:

```
sudo apt-get install python3 python3-pip
sudo pip3 install python-jose[cryptography]
```

(If you don't wish to install python-jose globally, or don't have root access,
you can use ```virtualenv``` or ```pip3 --user```)

To download and verify metadata:

```
./fetch_metadata.py --keys /path/to/jwks --output metadata.txt
```

The script will download from Skolfederation with a default URL, which can be
overridden with the `--url` argument.

## list_metadata
A script for listing entities from the metadata.

Before running the script you need to make sure that Python 3 and the
url-normalize package is installed.

For instance, to install on Debian these commands can be used:

```
sudo apt-get install python3 python3-pip
sudo pip3 install url-normalize
```

To list all entities:

```
./list_metadata.py metadata.txt
```

To list all server URIs:

```
./list_metadata.py --servers metadata.txt
```

To list all server tag combinations for a specific entity:

```
./list_metadata.py --server-tags --entity https://example.com metadata.txt
```
