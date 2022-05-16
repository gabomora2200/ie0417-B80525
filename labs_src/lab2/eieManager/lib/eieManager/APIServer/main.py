from fastapi import FastAPI

from ..DeviceManager.DevMan import DevMan
from ..APIServer.models import Device, Command
from ..args import parse_args


"""
Api initialization
"""
app = FastAPI()

"""
Args
"""
args = parse_args()

"""
device manager initialization
"""
device_manager = DevMan()
device_manager.init_devman(args.config)


@app.post("/devices/")
def create_device(device: Device):
    """
    Create a device and register it
    """
    res = device_manager.create_device(
        device.id, device.types, device.commands, device.net_info)
    return {"Response": res}


@app.post("/command/")
def get_command(command: Command):
    """
    Send a command and their info
    """
    res = device_manager.get_command(
        command.device_id, command.cmd, command.args)
    return {"Response": res}


@app.put("/devices/")
def update_device(device: Device):
    """
    Update a device
    """
    res = device_manager.update_device(
        device.id, device.types, device.commands, device.net_info)
    return {"Response": res}


@app.delete("/devices/{device_name}")
def delete_devices(device_name: str, status_code=204):
    """
    Unregister and delete a device.
    """
    res = device_manager.delete_devices(device_name)
    return {"Response": res}


@app.get("/devices/")
def devices_info():
    """
    Get the information of all devices
    """
    info = device_manager.devices_info()
    return info


@app.get("/devices/{device_name}")
def device_info(device_name: str):
    """
    Get the information of a device
    """
    info = device_manager.device_info(device_name)
    return info
