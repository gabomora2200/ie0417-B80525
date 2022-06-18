from pytest import fixture
import os
# NOTE: The fixtures here will be available for all tests.
# For more information about fixtures and conftest.py refer to:
# https://docs.pytest.org/en/7.1.x/how-to/fixtures.html


def pytest_addoption(parser):
    parser.addoption("--conf_dir", action="store", default="default conf_dir")


@fixture(scope='function')
def conf_filename():
    print("ENV VAR: ", os.environ.get('conf_dir'))
    return "/home/gabriel/Desktop/ie0417-B80525/labs_src/lab4/python/sensor_commands/config/sensors_cfg.json"


'''
@fixture(scope='function')
def example_func_fixt():
    logging.info("This is a function-scope example fixture!")
    data = {
        "name": "Data",
        "list": ["a", "b", "c"],
    }
    return data
    '''
