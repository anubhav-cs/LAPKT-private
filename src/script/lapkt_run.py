#!/usr/bin/env python3
import builtins
# from pathlib import Path
from argparse import ArgumentParser
# from importlib import import_module
from re import match
# from subprocess import run
# from os.path import join, isfile, isdir, dirname, realpath
from os import getpid

# LAPKT Imports
from run_planner import Run_planner, load_planner_config

# Parameters which must be set correctly

# rel_validate_file = Path('bin/validate')
# CWD = dirname(realpath(__file__))
"""
NOTE
Verify input against BUILTIN_TYPES to prevent
security issue with eval(...)
"""
BUILTIN_TYPES = [d for d in dir(builtins)
                 if isinstance(getattr(builtins, d), type)]
# -----------------------------------------------------------------------------#


def store_value(args, config) -> None:
    """A utility to generate config from cmd args

    :param args: attributes returned by ArgumentParser
    :type args: namespace
    :param config: planner run configuration
    :type config: dict
    """
    config['planner'] = dict()
    for k in dir(args):
        if match(r'^[^_]\w*', k):
            config.setdefault(k, dict())['value'] = getattr(args, k)


if __name__ == "__main__":
    parser_main = ArgumentParser(description="Process planner input")
    parser_sub = parser_main.add_subparsers(help='sub-command help')

    # Load the parsing args from the config file on PLANNER_CONFIG_PATH
    list_planner_config = load_planner_config()
    for k, options in list_planner_config.items():  # k is the planner name
        parser = parser_sub.add_parser(
            k, help='Use ' + k + ' -h' + ' to view planner options')
        # Add common config args
        parser.add_argument(
            '-d', '--domain', action='store', nargs='?',
            required=True, help='path to the domain pddl file')
        parser.add_argument(
            '-p', '--problem', action='store', nargs='?',
            required=True, help='path to the problem pddl file')
        parser.add_argument(
            '--no_match_tree', action='store_true',
            help='If specified, match tree is not generated')
        parser.add_argument(
            '--validate', action='store_true',
            help='If specified, plan is checked for correctioness' +
            'using validate')
        parser.add_argument(
            '--lapkt_instance_generator', action='store',
            nargs='?', default='Tarski',
            help='Choice of parser - Tarski<Default>,FD or FF')
        parser.add_argument(
            '--wait_debug', action='store_true', help='For' +
            ' debugging, program waits for key press while user attaches gdb')
        parser.set_defaults(planner=k)
        # Planner specific config
        for opt, parser_args in options.items():
            if isinstance(parser_args, dict) and \
                    parser_args.get('cmd_arg', None):
                has_type = parser_args['cmd_arg'].get('type', None)
                if has_type and has_type in BUILTIN_TYPES:
                    parser_args['cmd_arg']['type'] = eval(has_type)
                if parser_args['cmd_arg'].get('default', None):
                    parser_args['cmd_arg']['help'] = \
                        parser_args['cmd_arg']['help'] + "; **Default = " + \
                        str(parser_args['cmd_arg']['default'])
                parser.add_argument('--'+opt, **parser_args['cmd_arg'])
                del parser_args['cmd_arg']  # Will be in the Arg-parser

    args = parser_main.parse_args()

    try:
        config = list_planner_config[args.planner]
    except Exception:
        print("Use option '-h' for help")
        exit(0)

    if args.wait_debug:
        def exists_python_module(name):
            from importlib.util import find_spec as find_module
            try:
                return bool(find_module(name))
            except ImportError:
                return False

        def wait_debug(s):
            print("PID =", getpid(), ' ; ', s)
            input()

        if(exists_python_module('lapkt.tarski')):
            from lapkt.tarski import *
        if(exists_python_module('lapkt.ff')):
            from lapkt.ff import *

        wait_debug('Press a key to begin run...')

    store_value(args, config)
    run_status = Run_planner(config).solved
