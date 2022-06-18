from sensor_commands.sensor.sensor import Sensor


class MockSensor(Sensor):
    def __init__(self, name: str, stype: str, unit: str) -> None:
        super().__init__(name, stype, unit)
        self.pass_flag = 0

    def execute(self):
        super.execute()
        self.pass_flag = 1

    def assert_read(self):
        assert self.pass_flag == 1, "Read command was never executed "
