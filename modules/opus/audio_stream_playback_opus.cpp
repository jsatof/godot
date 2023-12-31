#include "audio_stream_playback_opus.h"

#include "core/math/math_funcs.h"

AudioStreamPlaybackExample::AudioStreamPlaybackExample()
	active(false) {

	AudioServer::get_singleton()->lock();
	AudioServer::get_singleton()->audio_data_alloc(PCM_BUFFER_SIZE);
	memset(pcm_buffer, 0, PCM_BUFFER_SIZE);
	AudioServer::get_singleton()->unlock();
}

AudioStreamPlaybackExample::~AudioStreamPlaybackExample() {
	if (pcm_buffer) {
		AudioServer::get_singleton()->audio_data_free(pcm_buffer);
		pcm_buffer = NULL;
	}
}

void AudioStreamPlaybackExample::start(float p_from_pos = 0.f)  {
	seek(p_from_pos);
	active = true;
}

void AudioStreamPlaybackExample::stop()  {
	active = false;
	base->reset();
}

bool AudioStreamPlaybackExample::is_playing() const  {
	return active;
}

int AudioStreamPlaybackExample::get_loop_count() const  {
	return 0;
}

float AudioStreamPlaybackExample::get_playback_position() const  {
	return 0.f;
}

void AudioStreamPlaybackExample::seek(float p_time)  {
	float max = get_length();
	if (p_time < 0) {
		p_time = 0.f;
	}

	base->set_position(uint64_t(p_time * base->mix_rate) << MIX_FRAC_BITS);
}

void AudioStreamPlaybackExample::mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames)  {
	ERR_FAIL_COND(!active);
	if (!active) {
		return;
	}

	memset(pcm_buffer, 0, PCM_BUFFER_SIZE);
	int16_t *buffer = (int16_t*)pcm_buffer;
	base->gen_tone(buffer, p_frames);

	for (int i = 0; i < p_frames; ++i) {
		float sample = float(buffer[i]) / 32767.0;
		p_buffer[i] = AudioFrame(sample, sample);
	}

}

float AudioStreamPlaybackExample::get_length() const  {
	return 0.f;
}
