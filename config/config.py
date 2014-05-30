
"""
Collects settings from the environment and adds them to the app configuration.

Flask specific settings will be set here and we can store additional settings
in the config object as well.
"""

import os
from os import environ
from sys import exit

# basedir = os.path.abspath(os.path.dirname(__file__))

try:
    # flask settings
    HOST = environ['HOST']
    PORT = environ['PORT']

		S3_ACCESS_KEY_ID=environ['S3_ACCESS_KEY_ID'] 
		S3_SECRET_ACCESS_KEY=environ['S3_SECRET_ACCESS_KEY']
		DEBUG = True if environ['DEBUG'] == 'TRUE' else False

    # mongodb settings
    # MDB_USER = environ['MDB_USER']
    # MDB_PASS = environ['MDB_PASS']
    # MDB_DB = environ['MDB_DB']
    # MDB_HOST = environ['MDB_HOST']
    # MDB_PORT = environ['MDB_PORT']

    # redis settings
    # REDIS_HOST = environ['REDIS_HOST']
    # REDIS_PORT = int(environ['REDIS_PORT'])
    # REDIS_DB = environ['REDIS_DB']

except KeyError:
    """ Throw an error if a setting is missing """
    print ("Some of your settings aren't in the environment."
           "You probably need to run:\n\n\tsource config/<your settings file>")
    exit(1)