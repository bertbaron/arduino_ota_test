[![Build Status](https://app.travis-ci.com/bertbaron/esp8266_ota_update.svg?branch=main)](https://app.travis-ci.com/bertbaron/esp8266_ota_update)

# Example project showing OTA updates from github releases

This project shows an easy process of publishing github releases and performing OTA updates from there. This is done by

* Using travis to build and upload tagged commits to github releases
* Using the library https://github.com/yknivag/ESP_OTA_GitHub to automatically update if a new release is detected

In addition the script https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266WiFi/examples/BearSSL_CertStore/certs-from-mozilla.py is slightly modified to reduce the number of certificates to include so that this all easily fits on a 1M d1_mini_lite.
## Creating releases

To create a new release, simply push a tag to the repository. The release will be build by Travis and uploaded to git.

The release tag is included in the firmware as current version which will be compared to the latest release. If there is a new release the update wil start automatically
## Getting started

Run `./init.py` to create the file system files with certificates and wifi credentials. These have to be uploaded once to the device. This way they will not end up in git. For your own project you may decide to use the WifiManager instead, in that case you can eliminate the wifi credentials part from the init and the code.

See https://docs.travis-ci.com/user/deployment/releases/ for how to setup travis uploads to github releases. You may want to follow the steps in this answer: https://stackoverflow.com/a/57032190/5379197 if you have trouble using `travis setup releases`.

## Test updates locally

By default no version will be set when run locally, and no update will be performed because of that. An easy way to test the update is to run something like the following from the platformio terminal:

```sh
TRAVIS_BRANCH=0 pio run --target upload
```

I didn't find another easy way to do this from Visual Studio Code without the risk of committing something I would regret, but please let me know if there is such a way.