# Spark Core App Thermostat: SCAT

This is the source code of the Spark Core App Thermostat. The app is heavily based on the official Spark app for android. I mainly changed the TinkerFragment.xml file and the corresponding activity. I also added basic functions to the ApiFacade file that allows for calling of any function on your Spark Core. I intent to make a "clean" version of this app, without the Thermostat, available soon.

This app assumes that the SCATFirmware is running on your core. The easiest way to do this is by opening the Spark IDE at www.spark.io/build and copy the content of the file SCATFirmware from the firmware folder to the IDE. Next, flash your core with the firmware. If you have the SCATFirmware in your Spark Account, you can reflash it from the app: I changed the "reflash tinker" function to reflash SCATFirmware instead.

The remainder of this readme is copied from the readme of the official Spark app for Android and mainly concerns instructions on how to locally build the app from the source code.

## Building
1. In Eclipse, go to File --> Import, and under the Android "folder", click "Existing Android Code into workspace", then click Next
2. Click Browse, select the dir where you cloned the repo, and click OK
3. You should now see two projects under the "Projects to Import" header: "SparkCore" and "Fontify".  Click on Finish.
4. In the SparkCore app, create the file ```res/values/local_build.xml``` with the following contents:

```
    <?xml version="1.0" encoding="utf-8"?>
    <resources>
        <string name="spark_token_creation_credentials">spark:spark</string>
    </resources>
```
_(You could actually put any valid HTTP Basic Auth string where it says ```spark:spark```; these values aren't currently used, but they must be present.)_

After this, you might also need to do a refresh and/or clean on the SparkCore project, because Eclipse. ;-)


## Required TI SmartConfig Library

You must add smartconfiglib.jar to the `SparkCore/libs` directory.

To get the SmartConfig library, go to the
[CC3000 Wi-Fi Downloads](http://processors.wiki.ti.com/index.php/CC3000_Wi-Fi_Downloads)
page. Search the page for the Android SmartConfig Application.
Download and unpack the app, which will require Windows. :-/
You can find smartconfiglib.jar in the libs directory of TI's app.

## Key Classes

If you want to know where the action is in the app, look at:
* SimpleSparkApiService: an IntentService which performs the actual HTTP calls to talk to the Spark Cloud
* ApiFacade: A simple interface for making requests and handling responses from the Spark API. If you want to work with the Spark API from Android, this is the place to start. See examples below like nameCore(), digitalWrite(), etc, for templates to work from.
* SparkCoreApp: There are a number of classes which rely on an initialization step during app startup.  All of this happens in SparkCoreApp.onCreate().


## Open Source Licenses

Original code in this repository is licensed by Spark Labs, Inc. under the Apache License, Version 2.0.
See LICENSE for more information.

This app uses several Open Source libraries. See SparkCore/libs/licenses for more information.
