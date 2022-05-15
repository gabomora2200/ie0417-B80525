from typing import Dict, Optional, List, Dict
import json

from . import command
from .Device.manager import DeviceManager



class DevMan():

    def __init__(self, config_path: str) -> None:
        self.config_path = config_path
        self.device_mgr = DeviceManager(config_path)
        self.cmd_runner = command.CommandRunner()
        
        


    def create_device(self, id: str, 
            d_type: str, 
            command: List[str], 
            net_info: str) -> str:

        self.device_mgr.set_new_device(id, d_type, command, net_info)

        with open(self.config_path) as config_file:
            config_info = json.load(config_file)
            print(config_info)

        return "ok"

    def get_command(self, id: str, cmd: str, 
            args: Optional[List[str]]) -> str:
    
        

        pass


    def update_device(self, id: str, 
            d_type: str, 
            command: List[str], 
            net_info: str) -> str:

        pass

    

    def delete_devices(self, id: str) -> str:

        pass

    def devices_info(self) -> Dict:

        pass

    def device_info(self, id:str) -> Dict:
        pass