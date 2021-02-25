//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}cids.h"

namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}} {

//------------------------------------------------------------------------
//  {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor
//------------------------------------------------------------------------
class {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor : public Steinberg::Vst::AudioEffect
{
public:
	{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor ();
	~{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor () SMTG_OVERRIDE;

    // Create function
	static Steinberg::FUnknown* createInstance (void* /*context*/) 
	{ 
		return (Steinberg::Vst::IAudioProcessor*)new {{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor; 
	}

	//--- ---------------------------------------------------------------------
	// AudioEffect overrides:
	//--- ---------------------------------------------------------------------
	/** Called at first after constructor */
	Steinberg::tresult PLUGIN_API initialize (Steinberg::FUnknown* context) SMTG_OVERRIDE;
	
	/** Called at the end before destructor */
	Steinberg::tresult PLUGIN_API terminate () SMTG_OVERRIDE;
	
	/** Switch the Plug-in on/off */
	Steinberg::tresult PLUGIN_API setActive (Steinberg::TBool state) SMTG_OVERRIDE;

	/** Will be called before any process call */
	Steinberg::tresult PLUGIN_API setupProcessing (Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;
	
	/** Asks if a given sample size is supported see SymbolicSampleSizes. */
	Steinberg::tresult PLUGIN_API canProcessSampleSize (Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

	/** Here we go...the process call */
	Steinberg::tresult PLUGIN_API process (Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;
		
	/** For persistence */
	Steinberg::tresult PLUGIN_API setState (Steinberg::IBStream* state) SMTG_OVERRIDE;
	Steinberg::tresult PLUGIN_API getState (Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:

  bool mBypass;

{%- for param in cookiecutter.settings.params %}
  {% if param.type == "range" %}
  float m{{param.name}}[k{{param.name}}ParamNum];
  {% elif param.type == "step" %}
  int m{{param.name}}[k{{param.name}}ParamNum];
  {% endif %}
{%- endfor -%}

void onInputParameterChanged(Steinberg::Vst::IParamValueQueue* paramQueue);

};

//------------------------------------------------------------------------
} // namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}}
