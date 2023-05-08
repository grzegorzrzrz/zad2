#!/bin/bash

docker run --rm --network-alias z33_python_client1 --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
docker run --rm --network-alias z33_python_client2 --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
docker run --rm --network-alias z33_python_client3 --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
docker run --rm --network-alias z33_python_client4 --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
docker run --rm --network-alias z33_python_client5 --hostname z33_python_client --network z33_network --name z33_python_client z33_task2_1_python_client $1 $2
