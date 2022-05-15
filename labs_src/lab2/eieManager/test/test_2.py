
#from ..lib.eieManager.DeviceManager import command
#from ..lib.eieManager.DeviceManager.Device.manager import DeviceManager
from eieManager.DeviceManager.DevMan import DevMan

import os

def main():
    """
    Device manager test
    """

    device_path = os.getcwd() + "/../config/Devices_lib.json"

    device_manager = DevMan(device_path)
    

    print(device_manager.device_info("Dev-02"))

    print(device_manager.devices_info())

    device_manager.create_device("Dev-100", "Alarm", ["Status"], "192.168.0.90:5000")

    print("\n\n")
    print(device_manager.devices_info())

    device_manager.update_device("Dev-100", "SecurityCamera", ["Status", "Set_device"], "192.168.1.90:7000")

    print("\n\n")
    print(device_manager.devices_info())

    device_manager.delete_devices("Dev-100")

    print("\n\n")
    print(device_manager.devices_info())





if __name__ == "__main__":
    main()