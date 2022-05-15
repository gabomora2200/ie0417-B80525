import json
from typing import Optional, List, Dict
from xmlrpc.client import _datetime_type

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

    def set_new_device(self, id: str, d_type: str, commands: List[str], net_info: str ) -> None:
        """
        Initializes a new device.
        :param str id: id of the new device.
        :param str d_type: type of device.
        :param List str commands: list of available device commands.
        :param str net_info: network information for a device.
        """
        self.devices[id] = self.device_factory(id, d_type, commands, net_info)
        self._init_devices_per_type()

    def update_device(self, id: str, d_type: str, commands: List[str], net_info: str ) -> None:
        """
        Updates a device.
        :param str id: id of the desired device.
        :param str d_type: type of device.
        :param List str commands: list of available device commands.
        :param str net_info: network information for a device.
        """
        self.devices[id].update_values(d_type, commands, net_info)
        #device.update_values(d_type, commands, net_info)
        #self.devices[id] = device 

                

    def delete_device(self, id: str) -> None:
        """
        Destroys a device by its ID.
        :param str id: id that points to the desired device.
        """
        dv = self.devices[id]
        del self.devices_per_type[dv.get_type()][id]
        del self.devices[id]

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

    def create_device_status_cmd(self, device_name: str) -> Command:
        """
        Creates a command to get a device status.

        :param str device_name: Name of the device to get status.
        :param device_name: Name of the device to get status.
        """
        device = self.devices[device_name]
        return DeviceStatusCommand(device)

    def create_device_set_device_cmd(self, device_name: str, args: List[str] = None ) -> Command:
        """
        Creates a command to set a device functionality.

        :param str device_name: Name of the device to set functionality.
        :param device_name: Name of the device to set functionality.
        """
        device = self.devices[device_name]
        return DeviceSetDeviceCommand(device, args)

    