from fastapi import FastAPI, Body
from typing import Optional
from pydantic import BaseModel

class Device(BaseModel):
    name: str
    type: str
    commands: List
    host: str

app = FastAPI()

@app.put("/devices/")
def update_device(device: Device):

    devices = device
    return device


@app.get("/devices/")
def devices_info():
    devices_list = [device for device in devices.values()]
    return devices_list

@app.get("/devices/{device_name}")
def device_info(device_name: str):

    return devices[device_name]

