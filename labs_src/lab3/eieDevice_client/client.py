import zmq
import struct
import json

from random import choice

string_list = ["Hola", "Mundo", "Este", "MAE", "EIE", "this"]
commands = ["message", "ping_pong", "status"]

"""
Function: create_payload
param: cmd (command name)
return:
    * payload
    * payload size
"""
def create_payload(cmd):
    if(cmd == "ping_pong"):
        payload = str({"arg"+str(i):choice(string_list) for i in range(1,6)}).replace("'", '"')
        size = len(payload)
    elif(cmd == "status"):
        payload = str({"arg1":choice(["is_active", "carga"])}).replace("'", '"')
        size = len(payload)
    else:
        payload = "{}"
        size = len(payload)
    
    return payload, size

"""
Function: fill the command name with spaces 
param: cmd (command name)
return:
    cmd (command name)
"""
def fill_char(cmd):
    cmd = cmd+'\0'
    while(len(cmd) < 100):
        cmd = " " + cmd
    
    return cmd

"""
Main function
"""
def main():
    port = 5555;
    context = zmq.Context()
    print("Connecting to server...")
    client = context.socket(zmq.REQ)
    with client.connect(f"tcp://localhost:{port}"):
        for i in range(100):
            #send request
            # Assuming little-endian in C side

            cmd = choice(commands)
            payload, size = create_payload(cmd)
            print("### Data Send ###")
            print("Command: ", cmd)
            print("Size: ", size)
            print("Payload: '", payload,"'")
             
            req = struct.pack("<100sI" + str(size) + "s", fill_char(cmd).encode(), size+1, (payload+'\0').encode())
            client.send(req)

            # # Receive response
            rep = client.recv()
            print("\nData Received: ", rep.decode(), "\n")
            
           
if __name__ == "__main__":
    main()
