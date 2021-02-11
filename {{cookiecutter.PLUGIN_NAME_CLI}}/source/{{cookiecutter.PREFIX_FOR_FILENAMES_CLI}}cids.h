//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}} {
//------------------------------------------------------------------------
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ProcessorUID (0x00000000, 0x11111111, 0x22222222, 0x33333333});
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ControllerUID (0x44444444, 0x55555555, 0x66666666, 0x77777777);

#define {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}VST3Category "{{cookiecutter.PLUGIN_CATEGORY_CLI}}"

//------------------------------------------------------------------------
} // namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}}
