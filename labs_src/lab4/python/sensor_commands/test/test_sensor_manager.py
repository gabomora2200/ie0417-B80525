from pytest import fixture
import logging
from sensor_commands.sensor.manager import SensorManager
from utils.rand_gen import RandomGenerator


class FixtureContext:
    def __init__(self):
        self.types = ["temperature", "level"]
        self.rng = RandomGenerator()
        self.names = ["sensor-eie" + str(i)
                      for i in self.rng.get_unique_int_list(0, 1000, 10)]


@fixture
def fixt_ctx():
    ctx = FixtureContext()
    logging.info("Fixture 0 Context Creation")
    return ctx


@fixture
def sensor_mgr(pytestconfig):
    logging.info("Fixture 1 setup (Creating Sensor)")
    smgr = SensorManager(pytestconfig.getoption("conf_dir"))
    return smgr


def test_sensor_manager_supported_types(sensor_mgr):
    sensor_name_list = sensor_mgr.get_supported_sensor_types()
    assert len(sensor_name_list) > 0, "Sensor name list length = 0"


def test_sensor_manager_single_sensor_read_command(fixt_ctx, sensor_mgr):
    sensor_name = fixt_ctx.rng.get_rand_list_item(fixt_ctx.names)
    sensor_type = fixt_ctx.rng.get_rand_list_item(fixt_ctx.types)
    print("sensor name: ", sensor_name, "\nsensor type: ", sensor_type)
    pass_flag = 0

    try:
        sensor_mgr.create_sensor(sensor_name, sensor_type)
        pass_flag = 1
    except BaseException:
        pass_flag = 0

    assert pass_flag == 1, "Can't Create Sensor"

    read_cmd = sensor_mgr.create_sensor_read_cmd(sensor_name)
    assert read_cmd is not None, "Invalid sensor read command creation"

    try:
        read_cmd.execute()
        pass_flag = 1
    except BaseException:
        pass_flag = 0

    assert pass_flag == 1, "Can't Execute Read Command"

    sensor_mgr.destroy_sensor(sensor_name)
    for i in sensor_mgr.get_sensors_info():
        assert i != sensor_name, "Could not Destroy sensor"
