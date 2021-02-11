# VST3 plugin cookiecutter

This repository contains VST3 plugin project template used by cookiecutter.
The template is based on VST3 Project generator(GUI) included in VST SDK version 3.7.1.

## Generate a VST3 plugin project

### Create a project from github repository directly

You can generate a VST3 Plugin project using cookiecutter from github repository directly.

```sh
$ cookiecutter gh:wrist/vst3_plugin_cookiecutter
VST3_SDK_PATH [./VST3_SDK]:
PLUGIN_NAME_CLI [MyVSTPlug]:
Select PLUGIN_CATEGORY_CLI:
1 - Fx
2 - Instrument
Choose from 1, 2 [1]:
CMAKE_PROJECT_NAME_CLI [MyVSTPlug]:
PLUGIN_BUNDLE_NAME_CLI [MyVSTPlug]:
PLUGIN_IDENTIFIER_CLI [com.company.myvstplug]:
VENDOR_NAME_CLI [VendorName]:
VENDOR_HOMEPAGE_CLI [https://example.com]:
VENDOR_EMAIL_CLI [email@example.com]:
PREFIX_FOR_FILENAMES_CLI [myvstplug]:
VENDOR_NAMESPACE_CLI [VendorNamespace]:
PLUGIN_CLASS_NAME_CLI [MyVSTPlug]:
Select ENABLE_VSTGUI_SUPPORT_CLI:
1 - ON
2 - OFF
Choose from 1, 2 [1]:

$ cd MyVSTPlug
```

But if you create a project in this way, you have to generate two uuid and replace the processor's and the controller's uids in `source/myvstplugcids.h` manually.

```sh
$ uuidgen  # please execute in your terminal, below string is just a example and it's hex values in fact.
XXXXXXXX-YYYY-YYYY-ZZZZ-ZZZZWWWWWWWW
$ uuidgen
AAAAAAAA-BBBB-BBBB-CCCC-CCCCDDDDDDDD
$ vim source/myvstplugcids.h
```

And put generated uuids to below argument as hex values.

```cpp
static const Steinberg::FUID kMyVSTPlugProcessorUID (0xXXXXXXXX,0xYYYYYYYY,0xZZZZZZZZ,0xWWWWWWWW);
static const Steinberg::FUID kMyVSTPlugControllerUID (0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD);
```

After that, you can build the project using cmake like below.

```sh
$ mkdir build
$ cd build
$ cmake .. -G "Xcode"  # for MacOS
$ cmake --build . --config debug  # or release
```

### Create a project from local repository cloned from github

If you clone this repository to local, you can automate the uuid generation process described above.
This generation process is realized by jinja2 extension, so you have to set `PYTHONPATH` variable environment to `extension` directory.

```sh
$ git clone https://github.com/wrist/vst3_plugin_cookiecutter.git
$ git checkout origin/uuid
$ export PYTHONPATH="${PYTHONPATH}:./vst3_plugin_cookiecutter/extensions"
$ cookiecutter vst3_plugin_cookiecutter
...
$ cd MyVSTPlug
$ mkdir build
$ cd build
$ cmake .. -G "Xcode"  # for MacOS
$ cmake --build . --config debug  # or release
```

## How to create this template structure

1. Download VST3 SDK from steinberg

```sh
$ wget https://download.steinberg.net/sdk_downloads/vst-sdk_3.7.1_build-50_2020-11-17.zip
$ unzip vst-sdk_3.7.1_build-50_2020-11-17.zip
```

2. Replace `@~@` symbols (which are used by `configure_file` of cmake) to jinja2 template using below script


```sh
#!/bin/bash

set -ue

cmake=`which cmake`
cmake_script="/path/to/VST_SDK/VST3_Project_Generator/macOS/VST3_Project_Generator.app/Contents/Resources/GenerateVST3Plugin.cmake"

OUTPUT_DIR="/path/to/cookiecutter_template_dir"

VST3_SDK_PATH="{{cookiecutter.VST3_SDK_PATH}}"
PLUGIN_NAME_CLI="{{cookiecutter.PLUGIN_NAME_CLI}}"
PLUGIN_CATEGORY_CLI="{{cookiecutter.PLUGIN_CATEGORY_CLI}}"
CMAKE_PROJECT_NAME_CLI="{{cookiecutter.CMAKE_PROJECT_NAME_CLI}}"
PLUGIN_BUNDLE_NAME_CLI="{{cookiecutter.PLUGIN_BUNDLE_NAME_CLI}}"
PLUGIN_IDENTIFIER_CLI="{{cookiecutter.PLUGIN_IDENTIFIER_CLI}}"
VENDOR_NAME_CLI="{{cookiecutter.VENDOR_NAME_CLI}}"
VENDOR_HOMEPAGE_CLI="{{cookiecutter.VENDOR_HOMEPAGE_CLI}}"
VENDOR_EMAIL_CLI="{{cookiecutter.VENDOR_EMAIL_CLI}}"
PREFIX_FOR_FILENAMES_CLI="{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}"
VENDOR_NAMESPACE_CLI="{{cookiecutter.VENDOR_NAMESPACE_CLI}}"
PLUGIN_CLASS_NAME_CLI="{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}"
ENABLE_VSTGUI_SUPPORT_CLI="{{cookiecutter.ENABLE_VSTGUI_SUPPORT_CLI}}"

${cmake} ${cmake_script} \
        -DSMTG_VST3_SDK_SOURCE_DIR_CLI=${VST3_SDK_PATH} \
        -DSMTG_GENERATOR_OUTPUT_DIRECTORY_CLI=${OUTPUT_DIR} \
        -DSMTG_PLUGIN_NAME_CLI=${PLUGIN_NAME_CLI} \
        -DSMTG_PLUGIN_CATEGORY_CLI=${PLUGIN_CATEGORY_CLI} \
        -DSMTG_CMAKE_PROJECT_NAME_CLI=${CMAKE_PROJECT_NAME_CLI} \
        -DSMTG_PLUGIN_BUNDLE_NAME_CLI=${PLUGIN_BUNDLE_NAME_CLI} \
        -DSMTG_PLUGIN_IDENTIFIER_CLI=${PLUGIN_IDENTIFIER_CLI} \
        -DSMTG_VENDOR_NAME_CLI=${VENDOR_NAME_CLI} \
        -DSMTG_VENDOR_HOMEPAGE_CLI=${VENDOR_HOMEPAGE_CLI} \
        -DSMTG_VENDOR_EMAIL_CLI=${VENDOR_EMAIL_CLI} \
        -DSMTG_PREFIX_FOR_FILENAMES_CLI=${PREFIX_FOR_FILENAMES_CLI} \
        -DSMTG_VENDOR_NAMESPACE_CLI=${VENDOR_NAMESPACE_CLI} \
        -DSMTG_PLUGIN_CLASS_NAME_CLI=${PLUGIN_CLASS_NAME_CLI} \
        -DSMTG_ENABLE_VSTGUI_SUPPORT_CLI=${ENABLE_VSTGUI_SUPPORT_CLI} \
        -P ${cmake_script}
```

3. Replace generated uuid by cmake to {{ uuid }} manually.
