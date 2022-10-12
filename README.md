LicenseServer
=============

This project sets out to create a simple self-hosted software activation server and client workflow.

Features
--------

- Allows anonymous demo the product
- Communicates encrypted
- Stores encrypted license files locally to allow offline running once activated
- New public/private keypairs for each product/version possible
- Allow activation codes via webhooks from fastspring/stripe etc.
- Allow transfer of licenses (configurable)
- Allow offline activation (configurable)

Dependencies
------------

- Client: 	JUCE/C++
- Server: 	Django / Heroku
- Database:	To be decided

JUCE is dual licenced. There is no license included when using this project.

Server
------

This repository can be deployed to a heroku server. To set this up follow the README in the `server` directory.

Protocol
--------

The client sends JSON packages contains a UID for the product/version to pick the correct private key for decryption.
It also contains a payload encryped and base64 encoded:

    {
      uid: "123e4567-e89b-12d3-a456-426614174000"
      payload: ""
    }

The payload looks like:

    {
      hardware: ""
      action: "demo"
      product: "Magic Ink"
      manufacturer: "ACME Inc."
      user: "123e4567-e89b-12d3-a456-426614174000"
    }

- hardware is a hardware ID as acquired via juce::SystemStats::getDeviceIdentifiers()
- action can be any of: "demo", "activate"
- product (optional) the product name
- manufacturer (optional) the manufacturer
- user (optional) if the license/demo is already connected to a user account it will be linked here
