import socket
import argparse
import threading

def handle_client(conn, addr):
    while True:
        data = conn.recv(1024)
        if not data:
            break
        #conn.sendall(data)
        print(f"Received {len(data)} bytes of data from: {addr}")
    print('Connection closed by client')
    conn.close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("name", help="Server name to listen at")
    parser.add_argument("port", help="Port number to listen at")
    args = parser.parse_args()

    name = args.name
    port = int(args.port)

    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((name, port))
        s.listen(5)

        while True:
            conn, addr = s.accept()
            thread = threading.Thread(target=handle_client, args=(conn, addr))
            thread.start()
            print(f"Active connections: {threading.active_count() - 1}")
