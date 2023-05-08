import socket
import argparse
from random import choices
import string
from time import sleep

def generate_data(size):
    rand_str = ''.join(choices(string.ascii_letters, k=size))
    return str.encode(rand_str)

DATA_SIZE = 64

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("server_name", help="Server's name")
    parser.add_argument("server_port", help="Server's port")

    args = parser.parse_args()

    server_name = args.server_name
    server_port = int(args.server_port)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:

        s.connect((server_name, server_port))

        for i in range(5):
            data = generate_data(20)
            s.sendall(data)
            print(f"Sending {len(data)} bytes of data to: ('{server_name}',{server_port})")
            sleep(0.5)