from typing import List
from abc import ABC

from ..command import Command


class Device(ABC):
    """
    Generic Device representation.

    :param str id: unique ID for each device.
    :param str type: Device type.
    :param list command: List of commands supported by the device.
    :param str net-info: ip and port.
    """

    def __init__(self, id: str,
                 d_type: str,
                 command: List[str],
                 net_info: str) -> None:
        self._id = id
        self._type = d_type
        self._command = command
        self._net_info = net_info

    def get_id(self) -> str:
        """
        Gets the id of the device.
        """
        return self._id

    def update_values(self,
                      d_type: str,
                      command: List[str],
                      net_info: str) -> None:
        self._type = d_type
        self._command = command
        self._net_info = net_info

    def get_type(self) -> str:
        """
        Gets device type.
        """
        return self._type

    def get_command(self) -> List:
        """
        Gets the commands supported by each device .
        """
        return self._command

    def get_net_info(self) -> str:
        """
        Gets the network info for each device .
        """
        return self._net_info

    def status(self) -> str:
        """
        Get the device's status info.
        :return: Device status.
        """
        pass

    def set_device(self, *args, **kwargs) -> None:
        """
        Set the device's functionality.
        """
        pass


class DeviceStatusCommand(Command):
    """
    Command to set Device status.

    :param device: Device object.
    :type device: :class:`Device`
    """

    def __init__(self, device: Device) -> None:
        self.device = device

    def execute(self) -> str:
        """
        Reads the device command and executes it.
        """
        name = self.device.get_id()
        d_type = self.device.get_type()
        read_value = self.device.status()
        response = f"DeviceStatusCommand: [{d_type}] {name}: {read_value}"
        print(response)
        return response


class DeviceSetDeviceCommand(Command):
    """
    Command to set Device functionality.

    :param device: Device object.
    :type device: :class:`Device`
    """

    def __init__(self, device: Device, args: List[str] = None) -> None:
        self.device = device
        self.args = args

    def execute(self) -> str:
        """
        Reads the device command and executes it.
        """
        name = self.device.get_id()
        d_type = self.device.get_type()
        self.device.set_device(self.args)
        response = f"DeviceSetDeviceCommand: [{d_type}] {name}: OK"
        print(response)
        return response
