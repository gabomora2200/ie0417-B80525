from argparse import ArgumentParser


def parse_args(argv=None):
    """
    Argument parsing routine.

    :param list argv: A list of argument strings.
    :return: A parsed and verified arguments namespace.
    :rtype: :py:class:`argparse.Namespace`
    """

    parser = ArgumentParser(
        description=(
            'sensor_commands is an example python package for the '
            'IE0417 course @ EIE, UCR'
        )
    )

    parser.add_argument(
        '-c', '--config',
        default="config/Devices_lib.json",
        help='Sensors configuration file',
    )

    args = parser.parse_args(argv)
    return args


__all__ = [
    'parse_args',
]
