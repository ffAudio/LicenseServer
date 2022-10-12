LicenseServer Server
====================

The server part of LicenseServer is a django app that is deployed to a heroku server.

Setup
-----

To develop this server, I followed this blog post:
https://medium.com/quick-code/deploying-django-app-to-heroku-full-guide-6ff7252578d7

Create a heroku app on https://www.heroku.com/. By connecting to this github repository it will run an instance of the django app.

Add a few environment variables in the heroku dashboard under "settings":

DJANGO_SECRET: add a secret key here, should be random. You can use get_random_secret_key() from your django installation:
    >>> from django.core.management.utils import get_random_secret_key
    >>> get_random_secret_key()

HEROKU_HOSTNAME: the hostname of your HEROKU server, so it can be accessed from outside

Connect a POSTGRES database, because the sqlite will be wiped every night when the heroku server does an automatic powercycle.

To be continued...
