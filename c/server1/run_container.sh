#!/bin/bash
docker run -d --rm -it --network-alias z33_c_server --hostname z33_c_server --network z33_network --name z33_c_server z33_task2_1_c_server 8000
