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
            'eie_manager_config'
        )
    )

    parser.add_argument(
        '-c', '--config',
        default="configs/",
        help='configuration directory',
    )

    args = parser.parse_args(argv)
    return args


__all__ = [
    'parse_args',
]
