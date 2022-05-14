"""
Devices entry point.
"""
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

    def __call__(self, name: str, stype: str) -> Sensor:
        """
        Creates the Device.

        :param str name: Name of the sensor to create.
        :param str stype: Sensor type.
        """
        sensor_cls = self._sensor_type_to_cls[stype]
        return sensor_cls(name)