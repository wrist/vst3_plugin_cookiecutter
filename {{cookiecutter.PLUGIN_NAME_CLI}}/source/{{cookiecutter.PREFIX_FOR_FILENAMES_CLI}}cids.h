//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}} {
//------------------------------------------------------------------------
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ProcessorUID ({{ processor_uid }});
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ControllerUID ({{ controller_uid }});

#define {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}VST3Category "{{cookiecutter.PLUGIN_CATEGORY_CLI}}"

//------------------------------------------------------------------------
} // namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}}
