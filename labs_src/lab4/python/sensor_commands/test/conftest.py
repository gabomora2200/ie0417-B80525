# NOTE: The fixtures here will be available for all tests.
# For more information about fixtures and conftest.py refer to:
# https://docs.pytest.org/en/7.1.x/how-to/fixtures.html


def pytest_addoption(parser):
    """
    function used to get config dir for test env
    """
    parser.addoption("--conf_dir", action="store", default="default conf_dir")
