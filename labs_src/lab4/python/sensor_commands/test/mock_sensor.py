from sensor_commands.sensor.sensor import Sensor


class MockSensor(Sensor):
    def __init__(self, name: str) -> None:
        super().__init__(name, "mock", "mock")
        self.pass_flag = 0

    def read(self) -> None:
        print("Read function execute")
        self.pass_flag = 1

    def assert_read(self):
        assert self.pass_flag == 1, "Read command was never executed "
