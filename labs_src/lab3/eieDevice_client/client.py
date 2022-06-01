# def main():
#     port = 5555;
#     context = zmq.Context()
#     print("Connecting to server...")
#     client = context.socket(zmq.REQ)
#     with client.connect(f"tcp://localhost:{port}"):
#         for i in range(10):
#             # Send request
#             # Assuming little-endian in C side
#             req_type = 2
#             req_val = 42 + i
#             req = struct.pack('<BI', req_type, req_val)
#             client.send(req)

#             # Receive response
#             rep = client.recv()
#             rep_val_a, rep_val_b = struct.unpack('<QB', rep)
#             print(f"Received response [val_a: {rep_val_a}, val_b: {rep_val_b}]")

import zmq
import struct
import json

from random import choice

string_list = ["Hola", "Mundo", "Este", "MAE", "Pura Vida", "EIE", "Software"]
commands = ["message", "ping_pong", "status"]

def create_payload(cmd):
    if (cmd == "ping_pong"):
        # payload = {"arg"+str(i):choice(string_list) for i in range(1,5)}
        payload = {"arg1":choice(["is_active", "carga"])}
        
    elif(cmd == "status"):
        payload = {"arg1":choice(["is_active", "carga"])}
    elif(cmd == "message"):
        payload = {}

    return str(payload).replace("'", '"'), len(str(payload).replace("'", '"'))


def fill_char(cmd):
    while(len(cmd) < 100):
        cmd = " " + cmd
    
    return cmd


def main():
    port = 5555;
    context = zmq.Context()
    print("Connecting to server...")
    client = context.socket(zmq.REQ)
    with client.connect(f"tcp://localhost:{port}"):
        for i in range(1000):
            #send request
            # Assuming little-endian in C side

            cmd = choice(commands)
            print(cmd)

            # if (cmd == "message"):
            #     req = struct.pack('<100cIs', fill_char(cmd).encode(), 1, "".encode())
            #     continue
            # else:
            payload, size = create_payload(cmd)
            print(payload)
            print(size)
             
            # print("\n########################\n")
            # code = "<100sI" + str(size) + "s"

            req = struct.pack("<100sI" + str(size) + "s", fill_char(cmd).encode(), size, payload.encode())
            
            
            # print(payload.replace("'", '"'))
            
            # print(type(json.loads(payload)))

            client.send(req)

            # # Receive response
            rep = client.recv()

            rep_data = struct.unpack('<I', rep)

            print(rep_data, "\n")
            # print(f"Received response [val_a: {rep_val_a}, val_b: {rep_val_b}]")
            # print(create_payload("status"))

            # print(req)            
            # print(struct.unpack('<100sI'+str(size)+'s', req))


if __name__ == "__main__":
    main()
