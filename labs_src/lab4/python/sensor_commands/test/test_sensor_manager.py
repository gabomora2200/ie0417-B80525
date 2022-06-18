from pytest import fixture
import logging
from sensor_commands.sensor.manager import SensorManager


@fixture
def sensor_mgr_ctx(pytestconfig):
    logging.info("Fixture 1 setup (Creating Sensor)")
    sensor_mgr = SensorManager(pytestconfig.getoption("conf_dir"))
    return sensor_mgr


def test_sensor_manager_supported_types(sensor_mgr_ctx):
    sensor_name_list = sensor_mgr_ctx.get_supported_sensor_types()
    assert len(sensor_name_list) > 0, "Sensor name list length = 0"


'''
def test_demo_api_add_op():
    r = demo_api.add(5, 9)
    logging.info(f"Add result: {r}")
    assert r == 14, "Addition failed!"


def test_demo_api_mult_op():
    r = demo_api.mult(5, 4)
    logging.info(f"Mult result: {r}")
    assert r == 20, "Multiplication failed!"


def test_demo_api_double_if_pos_op():
    r = demo_api.double_if_pos(5)
    logging.info(f"Double result: {r}")
    assert r == 10, "Double failed!"


def test_demo_api_double_if_pos_sanity():
    with pytest.raises(AssertionError):
        demo_api.double_if_pos(-4)
'''
