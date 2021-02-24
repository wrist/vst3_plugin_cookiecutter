//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}} {

{% for param in cookiecutter.settings.params -%}
const int k{{param.name}}ParamNum = {{param.num}};
const float k{{param.name}}ControllerMin = {{param.controller_min}}f;
const float k{{param.name}}ControllerMax = {{param.controller_max}}f;
const float k{{param.name}}ControllerDefault = {{param.controller_default}}f;
const float k{{param.name}}ProcessorMin = {{param.processor_min}}f;
const float k{{param.name}}ProcessorMax = {{param.processor_max}}f;
{% endfor %}

enum {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Params : Steinberg::Vst::ParamID {
  kBypass = 1,

{%- for param in cookiecutter.settings.params -%}
    {%- set num = param.num | int -%}
    {%- set id_offset = param.id_offset | int -%}
    {%- set is_last_param = loop.last -%}
    {%- for nth in range(num) %}
    k{{param.name}}{{nth}} = {{id_offset + nth}}{% if not (is_last_param and loop.last) %},{% endif %}
    {%- endfor -%}
{%- endfor %}
};

//------------------------------------------------------------------------
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ProcessorUID ({{ processor_uid }});
static const Steinberg::FUID k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ControllerUID ({{ controller_uid }});

#define {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}VST3Category "{{cookiecutter.PLUGIN_CATEGORY_CLI}}"

//------------------------------------------------------------------------
} // namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}}
