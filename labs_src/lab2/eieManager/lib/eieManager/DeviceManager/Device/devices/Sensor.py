from random import random

from ..Device import Device


class Sensor (Device):
    def __init__(self, id: str, 
            d_type: str, 
            command: List[], 
            net_info: str) -> None:
        super().__init__(id, d_type, command, net_info)

    def read()->float:
        return random.random()