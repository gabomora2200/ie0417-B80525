from fastapi import FastAPI, Body
from typing import Optional
from pydantic import BaseModel

class Device(BaseModel):
    id: str
    type: str
    commands: List[]
    host: str

class Command(BaseModel):
    device_id: str
    command: str
    args: Optional[List[]] = None

app = FastAPI()

@app.post("/items/")
def create_device(device: Device):
    """
    Create a device and register it
    """
    device_create = device
    return device_create


@app.post("/command/")
def create_device(command: Command):
    """
    Send a command and their info
    """
    command_send = command
    return command_send


@app.put("/devices/")
def update_device(device: Device):
    """
    Update a device
    """
    devices = device
    return device

@app.delete("/devices/{device_name}")
def delete_item(device_name: str, status_code=204):
    """
    Unregister and delete a device.
    """
    del devices[device_name]

@app.get("/devices/")
def devices_info():
    """
    Get the information of all devices
    """
    devices_list = [device for device in devices.values()]
    return devices_list

@app.get("/devices/{device_name}")
def device_info(device_name: str):
    """
    Get the information of a device
    """
    return devices[device_name]

