from typing import Dict, Optional, List
import json
from . import command
from .Device.manager import DeviceManager


class DevMan():
    def init_devman(self, config_path: str) -> None:
        self.config_path = config_path
        self.device_mgr = DeviceManager(config_path)
        self.cmd_runner = command.CommandRunner()
        self.cmd_runner.start()

        self.e = self.cmd_runner.event




    def create_device(self, id: str,
                      d_type: str,
                      _command: List[str],
                      net_info: str) -> str:
        self.device_mgr.set_new_device(id, d_type, _command, net_info)
        new_config = {}

        with open(self.config_path, 'r') as config_file:
            config_info = json.load(config_file)
            dvs = config_info["Devices"]
            dvs.append({"id": id, "type": d_type,
                       "commands": _command, "net_info": net_info})
            config_info["Devices"] = dvs
            new_config = config_info

        with open(self.config_path, 'w') as config_file:
            config_file.write(json.dumps(new_config, indent=4))

        return "ok"

    def get_command(self, id: str, cmd: str,
                    args: Optional[List[str]] = None) -> str:


        if(cmd == "Status"):
            print("Executing command")
            cmd_ex = self.device_mgr.create_device_status_cmd(id)
            self.cmd_runner.send(cmd_ex)
            self.e.wait()
            return self.cmd_runner.responses


        elif(cmd == "Set_device"):
            cmd_ex = self.device_mgr.create_device_set_device_cmd(id, args)
            self.cmd_runner.send(cmd_ex)
            self.e.wait()
            return self.cmd_runner.responses

        return "Command Not Found"

    def update_device(self, id: str,
                      d_type: str,
                      commands: List[str],
                      net_info: str) -> str:

        self.device_mgr.update_device(id, d_type, commands, net_info)

        new_config = {}
        with open(self.config_path, 'r') as config_file:
            config_info = json.load(config_file)
            dvs = config_info["Devices"]
            for i, d in enumerate(dvs):
                if (d["id"] == id):
                    dvs[i]["type"] = d_type
                    dvs[i]["commands"] = commands
                    dvs[i]["net_info"] = net_info
                    break
            config_info["Devices"] = dvs
            new_config = config_info
        with open(self.config_path, 'w') as config_file:
            config_file.write(json.dumps(new_config, indent=4))

        return "Ok"

    def delete_devices(self, id: str) -> str:

        self.device_mgr.delete_device(id)

        new_config = {}

        with open(self.config_path, 'r') as config_file:
            config_info = json.load(config_file)
            dvs = config_info["Devices"]
            rm = {}
            for d in dvs:
                if (d["id"] == id):
                    rm = d
                    break
            dvs.remove(rm)
            config_info["Devices"] = dvs
            new_config = config_info

        with open(self.config_path, 'w') as config_file:
            config_file.write(json.dumps(new_config, indent=4))

        return "Ok"

    def devices_info(self) -> Dict:
        config_info = {}
        with open(self.config_path, 'r') as config_file:
            config_info = json.load(config_file)

        return config_info

    def device_info(self, id: str) -> Dict:
        config_info = {}
        with open(self.config_path, 'r') as config_file:
            config_info = json.load(config_file)

        for dev in config_info["Devices"]:
            if (dev["id"] == id):
                return dev

        return {"Error": "Device not found"}
