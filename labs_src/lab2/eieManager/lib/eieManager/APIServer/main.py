from fastapi import FastAPI, Body
from typing import Optional, List
from pydantic import BaseModel
from ..DeviceManager import DeviceManager
import json

class Device(BaseModel):
    id: str
    types: str
    commands: List[str]
    net_info: str

class Command(BaseModel):
    device_id: str
    cmd: str
    args: Optional[List[str]] = None

app = FastAPI()

device_manager = DevMan()

'''
config = [
    ("Dev-01", "Sensor", ["Read"], "192.168.0.2:8000"),
    ("Dev-02", "Display", ["Status", "Set_device"], "192.168.0.3:8000"),
]


devices_inv = {
    id: Device(
        id = id,
        types = subdevice,
        commands = lists,
        net_info = info
    )
    for id, subdevice, lists, info in config
}
'''

@app.post("/devices/")
def create_device(device: Device):
    """
    Create a device and register it
    """
    device_manager.create_device(device.id, device.types, device.commands, device.net_info)
    devices_inv[device.id] = device
    return device


@app.post("/command/")
def get_command(command: Command):
    """
    Send a command and their info
    """
    device_manager.get_command(command.device_id, command.cmd, command.args)
    #commands[command.name] = command
    return command


@app.put("/devices/")
def update_device(device: Device):
    """
    Update a device
    """
    device_manager.create_device(device.id, device.types, device.commands, device.net_info)
    devices_inv[device.id] = device
    return device

@app.delete("/devices/{device_name}")
def delete_device(device_name: str, status_code=204):
    """
    Unregister and delete a device.
    """
    device_manager.delete_device(device.id, device.types, device.commands, device.net_info)
    del devices_inv[device_name]

@app.get("/devices/")
def devices_info():
    """
    Get the information of all devices
    """
    info = device_manager.devices_info()
    #devices_list = [device for device in devices_inv.values()]
    return json.dump(info)

@app.get("/devices/{device_name}")
def device_info(device_name: str):
    """
    Get the information of a device
    """
    info = device_manager.device_info(device_name)
    return info

