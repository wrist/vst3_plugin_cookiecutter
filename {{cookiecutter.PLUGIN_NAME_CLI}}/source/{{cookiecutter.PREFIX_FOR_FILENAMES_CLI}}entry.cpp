//------------------------------------------------------------------------
// Copyright(c) 2021 {{cookiecutter.VENDOR_NAME_CLI}}.
//------------------------------------------------------------------------

#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}processor.h"
#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}controller.h"
#include "{{cookiecutter.PREFIX_FOR_FILENAMES_CLI}}cids.h"
#include "version.h"

#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "{{cookiecutter.PLUGIN_NAME_CLI}}"

//------------------------------------------------------------------------
//  Module init/exit
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// called after library was loaded
bool InitModule ()
{
	return true;
}

//------------------------------------------------------------------------
// called after library is unloaded
bool DeinitModule ()
{
	return true;
}

using namespace Steinberg::Vst;
using namespace {{cookiecutter.VENDOR_NAMESPACE_CLI}};

//------------------------------------------------------------------------
//  VST Plug-in Entry
//------------------------------------------------------------------------
// Windows: do not forget to include a .def file in your project to export
// GetPluginFactory function!
//------------------------------------------------------------------------

BEGIN_FACTORY_DEF ("{{cookiecutter.VENDOR_NAME_CLI}}", 
			       "{{cookiecutter.VENDOR_HOMEPAGE_CLI}}", 
			       "mailto:{{cookiecutter.VENDOR_EMAIL_CLI}}")

	//---First Plug-in included in this factory-------
	// its kVstAudioEffectClass component
	DEF_CLASS2 (INLINE_UID_FROM_FUID(k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ProcessorUID),
				PClassInfo::kManyInstances,	// cardinality
				kVstAudioEffectClass,	// the component category (do not changed this)
				stringPluginName,		// here the Plug-in name (to be changed)
				Vst::kDistributable,	// means that component and controller could be distributed on different computers
				{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}VST3Category, // Subcategory for this Plug-in (to be changed)
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
				{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Processor::createInstance)	// function pointer called when this component should be instantiated

	// its kVstComponentControllerClass component
	DEF_CLASS2 (INLINE_UID_FROM_FUID (k{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}ControllerUID),
				PClassInfo::kManyInstances, // cardinality
				kVstComponentControllerClass,// the Controller category (do not changed this)
				stringPluginName "Controller",	// controller name (could be the same than component name)
				0,						// not used here
				"",						// not used here
				FULL_VERSION_STR,		// Plug-in version (to be changed)
				kVstVersionString,		// the VST 3 SDK version (do not changed this, use always this define)
				{{cookiecutter.PLUGIN_CLASS_NAME_CLI}}Controller::createInstance)// function pointer called when this component should be instantiated

	//----for others Plug-ins contained in this factory, put like for the first Plug-in different DEF_CLASS2---

END_FACTORY
