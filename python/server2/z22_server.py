import socket
import argparse

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

        conn, addr = s.accept()

        full_mess = ""
        while True:
            data = conn.recv(60)
            if not data:
                print(f"Full mess: {full_mess}")
                print("\n==============================\n")
            else:
                print(f"Mess: {data.decode('utf-8')} from {addr}")
                full_mess += data.decode('utf-8')