#!/bin/bash

docker run --rm -it --network-alias z33_c_client --hostname z33_c_client --network z33_network --name z33_c_client z33_task2_1_c_client $1 $2
