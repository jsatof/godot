#include "register_types.h"

#include "core/object/class_db.h"

#include "audio_stream_opus.h"
#include "audio_stream_playback_opus.h"

void initialize_opus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<AudioStreamExample>();
	ClassDB::register_class<AudioStreamPlaybackExample>();
}

void uninitialize_opus_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}
