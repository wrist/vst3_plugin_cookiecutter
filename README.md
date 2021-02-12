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

But if you create a project in this way, you have to generate two uuids and replace the processor's and the controller's uids in `source/myvstplugcids.h` manually.

```sh
$ uuidgen  # please execute in your terminal, the below string is just an example instead of generated hex values.
XXXXXXXX-YYYY-YYYY-ZZZZ-ZZZZWWWWWWWW
$ uuidgen
AAAAAAAA-BBBB-BBBB-CCCC-CCCCDDDDDDDD
$ vim source/myvstplugcids.h
```

And put generated uuids to the below function's arguments as hex values.

```cpp
static const Steinberg::FUID kMyVSTPlugProcessorUID (0xXXXXXXXX,0xYYYYYYYY,0xZZZZZZZZ,0xWWWWWWWW);
static const Steinberg::FUID kMyVSTPlugControllerUID (0xAAAAAAAA,0xBBBBBBBB,0xCCCCCCCC,0xDDDDDDDD);
```

After that, you can build the project using cmake like below.

```sh
$ mkdir build
$ cd build
$ cmake .. -G "Visual Studio 16 2019" -A "x64" # for Windows
$ cmake .. -G "Xcode"  # for MacOS
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Ninja"  # for Linux, using Ninja build
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
$ cmake .. -G "Visual Studio 16 2019" -A "x64" # for Windows
$ cmake .. -G "Xcode"  # for MacOS
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Ninja"  # for Linux, using Ninja build
$ cmake --build . --config debug  # or release
```

### Apt packages required to build a plugin on `Ubuntu 20.04`

Below apt packages are required to build a plugin on `Ubuntu 20.04.02 LTS`.

```sh
$ sudo apt install build-essential
$ sudo apt install ninja-build  # in case of building using Ninja
$ sudo apt install libx11-dev libfreetype6-dev pkg-config libgtk-3-dev libgtkmm-3.0-dev
$ sudo apt install libxcb-util-dev libxcb-cursor-dev libxcb-keysyms1-dev libxcb-xkb-dev libxkbcommon-dev libxkbcommon-x11-dev
$ sudo apt install libjack-jack2-dev  # if you need jack support
```

## How to create jinja2 template from cmake files in VST3 SDK

1. Download VST3 SDK from steinberg

```sh
$ wget https://download.steinberg.net/sdk_downloads/vst-sdk_3.7.1_build-50_2020-11-17.zip
$ unzip vst-sdk_3.7.1_build-50_2020-11-17.zip
```

2. Replace `@~@` symbols (which are used by `configure_file` of cmake) to jinja2 template using the below script


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

3. (for uuid branch) Replace uuids generated by cmake to `{{ processor_uid }}` and `{{ controller_uid }}`` manually.


## License of original VST3 Project Generator

Original VST3 Project Generator is distributed with the below BSD-3-clause license.

```
//-----------------------------------------------------------------------------
// LICENSE
// (c) 2020, Steinberg Media Technologies GmbH, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------
```
