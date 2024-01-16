#include "audio_stream_ogg_opus.h"

#include "core/math/math_funcs.h"

int AudioStreamPlaybackOpus::_mix_internal(AudioFrame *p_buffer, int p_frames) {
	return 0;
}

AudioStreamPlaybackOpus::AudioStreamPlaybackOpus()
	: active(false)
{
	AudioServer::get_singleton()->lock();
	//AudioServer::get_singleton()->audio_data_alloc(PCM_BUFFER_SIZE);
	memalloc(PCM_BUFFER_SIZE);
	memset(pcm_buffer, 0, PCM_BUFFER_SIZE);
	AudioServer::get_singleton()->unlock();
}

AudioStreamPlaybackOpus::~AudioStreamPlaybackOpus() {
	if (pcm_buffer) {
		AudioServer::get_singleton()->audio_data_free(pcm_buffer);
		pcm_buffer = NULL;
	}
}

void AudioStreamPlaybackOpus::start(float p_from_pos)  {
	seek(p_from_pos);
	active = true;
}

void AudioStreamPlaybackOpus::stop()  {
	active = false;
	base->reset();
}

bool AudioStreamPlaybackOpus::is_playing() const  {
	return active;
}

int AudioStreamPlaybackOpus::get_loop_count() const  {
	return 0;
}

void AudioStreamPlaybackOpus::seek(float p_time)  {
	float max = get_length();
	if (p_time < 0) {
		p_time = 0.f;
	}

	base->set_position(uint64_t(p_time * base->mix_rate) << MIX_FRAC_BITS);
}

//void AudioStreamPlaybackOpus::mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames)  {
//	ERR_FAIL_COND(!active);
//	if (!active) {
//		return;
//	}
//
//	memset(pcm_buffer, 0, PCM_BUFFER_SIZE);
//	int16_t *buffer = (int16_t*)pcm_buffer;
//	base->gen_tone(buffer, p_frames);
//
//	for (int i = 0; i < p_frames; ++i) {
//		float sample = float(buffer[i]) / 32767.0;
//		p_buffer[i] = AudioFrame(sample, sample);
//	}
//
//}

double AudioStreamPlaybackOpus::get_length() const  {
	return 0.f;
}


////////////////////////////////////////////////////////


AudioStreamOpus::AudioStreamOpus()
	: mix_rate(44100)
	, stereo(false)
	, hz(639)
{}

void AudioStreamOpus::reset() {
	set_position(0);
}

void AudioStreamOpus::set_position(uint64_t p_pos) {
	pos = p_pos;
}

Ref<AudioStreamPlayback> AudioStreamOpus::instantiate_playback() {
	Ref<AudioStreamPlaybackOpus> talking_tree;
	talking_tree.instantiate();
	talking_tree->base = Ref<AudioStreamOpus>(this);
	return talking_tree;
}

String AudioStreamOpus::get_stream_name() const {
	return "AudioStreamOpus";
}

void AudioStreamOpus::gen_tone(int16_t *pcm_buffer, int size) {
	for (int i = 0; i < size; ++i) {
		pcm_buffer[i] = 32767.0 * sin(2.0 * Math_PI * double(pos + i) / (double(mix_rate) / double(hz)));
	}
	pos += size;
}

void AudioStreamOpus::_bind_methods() {
	ClassDB::bind_method(D_METHOD("reset"), &AudioStreamOpus::reset);
	ClassDB::bind_method(D_METHOD("get_stream_name"), &AudioStreamOpus::get_stream_name);
}
