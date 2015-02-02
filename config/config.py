from os import environ
from sys import exit

"""
Collects settings from the environment and adds them to the app configuration.

Flask specific settings will be set here and we can store additional settings
in the config object as well.
"""

try:
    # Flask settings
    HOST = environ['HOST']
    PORT = environ['PORT']
    DEBUG = True if environ['DEBUG'] == 'TRUE' else False

    # S3 settings
    S3_ACCESS_KEY_ID=environ['S3_ACCESS_KEY_ID']
    S3_SECRET_ACCESS_KEY=environ['S3_SECRET_ACCESS_KEY']
    S3_BUCKET_NAME=environ['S3_BUCKET_NAME']

except KeyError:
    """ Throw an error if a setting is missing """
    print ("Some of your settings aren't in the environment."
           "You probably need to run:\n\n\tsource config/<your settings file>")
    exit(1)
