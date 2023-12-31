#include "audio_stream_opus.h"

#include "audio_stream_playback_opus.h"

AudioStreamExample::AudioStreamExample()
	: mix_rate(44100)
	, stereo(false)
	, hz(639)
{}

void AudioStreamExample::reset() {
	set_position(0);
}

void AudioStreamExample::set_position(uint64_t p_pos) {
	pos = p_pos;
}

Ref<AudioStreamPlayback> AudioStreamExample::instance_playback() {
	Ref<AudioStreamPlaybackExample> talking_tree;
	talking_tree.instantiate();
	talking_tree->base = Ref<AudioStreamExample>(this);
	return talking_tree;
}

String AudioStreamExample::get_stream_name() const {
	return "AudioStreamExample";
}

void AudioStreamExample::gen_tone(uint16_t *pcm_buffer, int size) {
	for (int i = 0; i < size; ++i) {
		pcm_buffer[i] = 32767.0 * sin(2.0 * Math_PI * double(pos + i) / (double(mix_rate) / double(hz)));
	}
	pos += size;
}

void AudioStreamExample::_bind_methods() {
	ClassDB::bind_method(D_METHOD("reset"), &AudioStreamExample::reset);
	ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioStreamExample::get_stream_name);
}
