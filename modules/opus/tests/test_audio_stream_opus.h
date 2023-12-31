#ifndef SEEN_TEST_AUDIO_STREAM_OPUS
#define SEEN_TEST_AUDIO_STREAM_OPUS

#include "test/test_macros.h"
#include "modules/opus/audio_stream_opus.h"
#include "modules/opus/audio_stream_playback_opus.h"

namespace TestAudioStreamOpus {

TestCase("[Modules][AudioStreamOpus] AudioStreamOpus") {
	Ref<AudioStreamExample> = memnew(AudioStreamExample);
	CHECK(true);
}

}

#endif
