#!/bin/bash
proto_dir=./
proto_src=./pb_src
rm -rf pb_src
mkdir pb_src
protoc -I=$proto_dir --cpp_out=$proto_src $proto_dir/*.proto --experimental_allow_proto3_optional