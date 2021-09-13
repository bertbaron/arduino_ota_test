#!/usr/bin/env python3
import certs_from_mozilla # will run the certs-from-mozilla script
import json
from getpass import getpass

settings = {}
print()
print("Enter the wifi credentials, these will be written to data/settings.json")
settings['ssid']=input("ssid: ")
settings['password']=getpass('password: ')

with open('data/settings.json', 'w') as outfile:
    json.dump(settings, outfile)

print()
print("data/certs.ar and data/settings.json have been written")
print("these can be uploaded from vscode using Platform/Upload Filesystem Image")
print("or with: pio run --target uploadfs")
print()
print("After uploading the file system to your device the data folder may be removed")