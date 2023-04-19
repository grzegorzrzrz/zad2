#!/bin/bash

docker run --rm -it --network-alias z33_python_client --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
