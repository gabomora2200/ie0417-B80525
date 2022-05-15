from random import choice
from typing import List

from ..Device import Device


class Alarm (Device):
    def __init__(self, id: str, 
            d_type: str, 
            command: List[str], 
            net_info: str) -> None:
        super().__init__(id, d_type, command, net_info)

    def status(self) -> str:
        """
        Return a random value
        """
        print("Executing status command")
        return choice(["ARMED", "DISARMED"])

    def set_device(self, *args, **kwargs) -> None:
        print("Executing set_device command")
        for arg in args:
            print(f"arg: {arg}")
