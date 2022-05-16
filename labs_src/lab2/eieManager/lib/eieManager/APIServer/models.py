from typing import Optional, List
from pydantic import BaseModel

class Device(BaseModel):
    id: str
    types: str
    commands: List[str]
    net_info: str

class Command(BaseModel):
    device_id: str
    cmd: str
    args: Optional[List[str]] = None


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