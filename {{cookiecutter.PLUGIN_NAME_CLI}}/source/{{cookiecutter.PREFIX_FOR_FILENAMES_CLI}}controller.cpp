//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}controller.h"
#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}cids.h"
#include "vstgui/plugin-bindings/vst3editor.h"

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
