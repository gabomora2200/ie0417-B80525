"""
Devices entry point.
"""
from typing import List
from ..Device import Device

from .Sensor import Sensor
from .SecurityCamera import SecurityCamera
from .HomeDevice import HomeDevice
from .Display import Display
from .Alarm import Alarm


class DeviceFactory():
    """
    Factory that creates a Device of a given type name.
    """
    def __init__(self) -> None:
        # Dictionary that maps names of device types to classes.
        self._device_type_to_cls = {
            "Sensor": Sensor,
            "Display": Display,
            "Alarm": Alarm,
            "HomeDevice": HomeDevice,
            "SecurityCamera": SecurityCamera,
        }

    @property
    def supported_types(self):
        """
        Returns the list of names for the supported device types.
        """
        return [stype for stype in self._device_type_to_cls.keys()]

    def __call__(self, name: str, stype: str) -> Device:
        """
        Creates the Device.

        :param str name: Name of the device to create.
        :param str stype: Device type.
        :param list commands: List of device commands.
        :param str netInfo: Device network information
        """
        device_cls = self._device_type_to_cls[stype]
        print(device_cls)
        return device_cls(name)