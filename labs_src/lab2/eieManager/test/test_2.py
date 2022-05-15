
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
    
    

    device_mgr = DeviceManager(device_path)
    device_cmd_runner = command.CommandRunner()

    device_cmd_runner.start()


    device_ex = device_mgr.create_device_status_cmd("Dev-03")
    device_cmd_runner.send(device_ex)

    device_ex = device_mgr.create_device_status_cmd("Dev-02")
    device_cmd_runner.send(device_ex)

    device_cmd_runner.stop()
    



if __name__ == "__main__":
    main()