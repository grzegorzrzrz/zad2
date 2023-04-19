#!/bin/bash

sh ./create_container.sh
sleep 2s
reset
echo "
Container created
"
docker images | grep z33_task2_1_python_client
sleep 5s
reset
echo "
Running container...
"
sh ./run_container.sh $1 $2
sleep 2s
reset