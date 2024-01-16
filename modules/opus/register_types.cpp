#include "register_types.h"

#include "core/object/class_db.h"

#include "audio_stream_ogg_opus.h"

void initialize_opus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<AudioStreamOpus>();
	ClassDB::register_class<AudioStreamPlaybackOpus>();
}

void uninitialize_opus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
