import json
from typing import Optional, List, Dict


from ..command import Command
from .devices import DeviceFactory
from .Device import Device, DeviceReadCommand, DeviceStatusCommand, DeviceSetDeviceCommand


class DeviceManager:
    """
    Manager class to control device objects lifecycle.

    :param str config_filename: Name of the file with the device config.
    """
    def __init__(self, config_filename: str) -> None:
        self.config_filename = config_filename
        self.device_factory = DeviceFactory()
        self.devices: Dict[str, Device] = {}
        self.devices_per_type: Dict[str, Dict[str, Device]] = {}
        self.init_config()

    def _init_devices_per_type(self):
        """
        Initializes a devices per-type mapping dictionary.
        """
        for device in self.devices.values():
            stype = device.get_type()
            id = device.get_id()
            if stype not in self.devices_per_type:
                self.devices_per_type[stype] = {}
            self.devices_per_type[stype][id] = device

    def init_config(self) -> None:
        """
        Initializes the device manager configuration.
        """
        # Parse config file
        with open(self.config_filename) as config_file:
            config_info = json.load(config_file)
            devices_info = config_info["Devices"]
            # Create devices
            for device_info in devices_info:
                name = device_info["id"]
                stype = device_info["type"]
                cmd = device_info["commands"]
                net_if = device_info["net_info"]
                self.devices[name] = self.device_factory(name, stype, cmd, net_if)
        self._init_devices_per_type()

    def get_device_types(self) -> List[str]:
        """
        Returns the list of device types.
        """
        return [id for id in self.devices_per_type.keys()]

    def get_device_id(self) -> List[str]:
        """
        Returns the list of device names.
        """
        return [id for id in self.devices.keys()]

    def get_device_id_per_type(self, stype: str) -> List[str]:
        """
        Returns the list of device names for a sensor type.
        """
        ids: List[str] = []
        type_devices = self.devices_per_type.get(stype)
        if type_devices is not None:
            ids = [id for id in type_devices.keys()]
        return ids

    def create_device_read_cmd(self, device_name: str) -> Command:
        """
        Creates a command to read a device data.

        :param str device_name: Name of the device to read.
        :param device_name: Name of the device to read.
        """
        device = self.devices[device_name]
        return DeviceReadCommand(device)

    def create_device_status_cmd(self, device_name: str) -> Command:
        """
        Creates a command to get a device status.

        :param str device_name: Name of the device to get status.
        :param device_name: Name of the device to get status.
        """
        device = self.devices[device_name]
        return DeviceStatusCommand(device)

    def create_device_set_device_cmd(self, device_name: str) -> Command:
        """
        Creates a command to set a device functionality.

        :param str device_name: Name of the device to set functionality.
        :param device_name: Name of the device to set functionality.
        """
        device = self.devices[device_name]
        return DeviceSetDeviceCommand(device)