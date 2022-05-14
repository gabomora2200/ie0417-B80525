from random import choice

from ..Device import Device


class HomeDevice (Device):
    def __init__(self, id: str, 
            d_type: str, 
            command: List[], 
            net_info: str) -> None:
        super().__init__(id, d_type, command, net_info)

    def status(self) -> str:
        """
        Return a random value
        """
        return choice(["Executing", "OFF"])

    def set_device(self, *args, **kwargs) -> None:
        for arg in args:
            print(f"arg: {arg}")