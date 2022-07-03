"""
Main file
"""

from time import sleep
from .utils.args import parse_args

from .ditto.policies import set_policy
from .ditto.connections import set_connection


def main(*args):
    if len(args) == 0:
        my_args = parse_args()
        config_dir = my_args.config
    else:
        config_dir = args[0]

    """
    Lo primero que se debe hacer es configurar las politicas de acceso
    y establecer las conexiones de source-target al broker de MQTT
    """
    sleep(60)
    
    with open(f"{config_dir}/base_policy.json", 'r') as file:
        policy = file.read()

    print(set_policy("my.test:policy", policy))

    with open(f"{config_dir}/base_connection.json", 'r') as file:
        connection = file.read()

    print(print(set_connection(connection)))


if __name__ == "__main__":
    main(None)
