#!/bin/bash

sh ./create_container.sh
sleep 2s
reset
echo "
Container created
"
docker images | grep z33_task2_1_c_server
sleep 5s
reset
echo "
Running container...
"
sh ./run_container.sh
echo "
Container created"
docker ps | grep z33_task2_1_c_server
sleep 3s
clear
docker logs --follow z33_c_server