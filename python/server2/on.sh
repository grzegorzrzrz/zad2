#!/bin/bash

sh ./create_container.sh
sleep 2s
reset
echo "
Container created
"
docker images | grep z33_task2_2_python_server
sleep 5s
reset
echo "
Running container...
"
sh ./run_container.sh
echo "
Container created"
docker ps | grep z33_task2_2_python_server
sleep 3s
clear
docker logs --follow z33_python_server