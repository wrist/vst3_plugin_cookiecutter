//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}controller.h"
#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}cids.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "base/source/fstreamer.h"

using namespace Steinberg;

namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}} {

//------------------------------------------------------------------------
// {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::initialize (FUnknown* context)
{
	// Here the Plug-in will be instanciated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
    parameters.addParameter(STR16("Bypass"), nullptr, 1, 0,
        Vst::ParameterInfo::kCanAutomate | Vst::ParameterInfo::kIsBypass, kBypass);

{%- for param in cookiecutter.settings.params %}
  {% if param.type == "range" %}
    {
        // RangeParameter(title, tag, units, minPlain, maxPlain, defaultValuePlain, stepCount, flags)
        Vst::RangeParameter* p{{param.name}};
        int param_id = k{{param.name}}0;
        String param_str("{{param.name}}0");
        for(int ch = 0; ch < k{{param.name}}ParamNum; ch++){
          p{{param.name}} = new Vst::RangeParameter(param_str, param_id + ch, STR16("{{param.title}}"),
              k{{param.name}}ControllerMin, k{{param.name}}ControllerMax, k{{param.name}}ControllerDefault,
              0L, Vst::ParameterInfo::kCanAutomate);
          p{{param.name}}->setPrecision({{param.precision}});
          parameters.addParameter(p{{param.name}});

          param_str.incrementTrailingNumber(/* width = */ 1, /* separator = */ ConstString("")[0]);
      }
    }
  {% elif param.type == "step" %}
    {
        int param_id = k{{param.name}}0;
        String param_str("{{param.name}}0");
        for(int ch = 0; ch < k{{param.name}}ParamNum; ch++){
          Vst::StringListParameter* p{{param.name}} = new Vst::StringListParameter(param_str, param_id + ch);

          {% for item in param.options %}
          p{{param.name}}->appendString(STR16("{{item}}"));
          {%- endfor %}

          parameters.addParameter(p{{param.name}});

          param_str.incrementTrailingNumber(/* width = */ 1, /* separator = */ ConstString("")[0]);
      }
    }
  {% endif %}
{%- endfor -%}


	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::terminate ()
{
	// Here the Plug-in will be de-instanciated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::setComponentState (IBStream* state)
{
	// Here you get the state of the component (Processor part)
	if (!state)
		return kResultFalse;

  IBStreamer streamer(state, kLittleEndian);

{%- for param in cookiecutter.settings.params %}
    {
        float param_state;
        int param_id = k{{param.name}}0;
        String param_str("{{param.name}}0");
        for(int ch = 0; ch < k{{param.name}}ParamNum; ch++){
          if(streamer.readFloat(param_state) == false) { return kResultFalse; }
          setParamNormalized(param_id + ch, param_state);
        }
    }
{%- endfor -%}

    // read the bypass
    int32 bypassState;
    if(streamer.readInt32(bypassState) == false){ return kResultFalse; }
    setParamNormalized(kBypass, bypassState ? 1 : 0);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}editor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::setParamNormalized (Vst::ParamID tag, Vst::ParamValue value)
{
	// called by host to update your parameters
	tresult result = EditControllerEx1::setParamNormalized (tag, value);
	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::getParamStringByValue (Vst::ParamID tag, Vst::ParamValue valueNormalized, Vst::String128 string)
{
	// called by host to get a string for given normalized value of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamStringByValue (tag, valueNormalized, string);
}

//------------------------------------------------------------------------
tresult PLUGIN_API {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::getParamValueByString (Vst::ParamID tag, Vst::TChar* string, Vst::ParamValue& valueNormalized)
{
	// called by host to get a normalized value from a string representation of a specific parameter
	// (without having to set the value!)
	return EditControllerEx1::getParamValueByString (tag, string, valueNormalized);
}

//------------------------------------------------------------------------
} // namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}}
