#!/bin/bash

docker run -d --rm -it --network-alias z33_python_server --hostname z33_python_server --network z33_network --name z33_python_server z33_task2_1_python_server z33_python_server 8001
