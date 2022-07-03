import pytest
# from pytest import fixture
import logging
from eie_manager_config import main
from utils.rand_gen import RandomGenerator


class FixtureContext:
    def __init__(self):
        self.rng = RandomGenerator()


@pytest.fixture
def fixt_ctx():
    ctx = FixtureContext()
    logging.info("Fixture 0 Context Creation (RandomGenerator)")
    return ctx


# -----------------------------------------------------------------
# Tests
# -----------------------------------------------------------------

def test_eie_manager_base(pytestconfig):
    print("test 1")
    main.main(pytestconfig.getoption("conf_dir"))
    assert 1 == 1, "base test assertion"
