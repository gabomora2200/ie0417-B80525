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
    device_manager.create_device(
        device.id, device.types, device.commands, device.net_info)
    return device


@app.post("/command/")
def get_command(command: Command):
    """
    Send a command and their info
    """
    device_manager.get_command(command.device_id, command.cmd, command.args)
    return command


@app.put("/devices/")
def update_device(device: Device):
    """
    Update a device
    """
    device_manager.update_device(
        device.id, device.types, device.commands, device.net_info)
    return device


@app.delete("/devices/{device_name}")
def delete_device(device_name: str, status_code=204):
    """
    Unregister and delete a device.
    """
    device_manager.delete_device(device_name)


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


def get_app():
    """
    returns the app instance
    """
    return app
