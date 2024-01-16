#ifndef SEEN_AUDIO_STREAM_OGG_OPUS
#define SEEN_AUDIO_STREAM_OGG_OPUS

#include "servers/audio/audio_stream.h"

class AudioStreamOpus: public AudioStream {
	GDCLASS(AudioStreamOpus, AudioStream)	

	friend class AudioStreamPlaybackOpus;
	uint64_t pos;
	int mix_rate;
	bool stereo;
	int hz;

protected:
	static void _bind_methods();

public:
	void reset();
	void set_position(uint64_t pos);
	virtual Ref<AudioStreamPlayback> instantiate_playback();
	String get_stream_name() const;
	void gen_tone(int16_t *pcm_buffer, int size);
	virtual double get_length() const;
	AudioStreamOpus();
};


class AudioStreamPlaybackOpus : public AudioStreamPlayback {
	GDCLASS(AudioStreamPlaybackOpus, AudioStreamPlayback)

	friend class AudioStreamOpus;

	enum {
		PCM_BUFFER_SIZE = 4096,
	};

	enum {
		MIX_FRAC_BITS = 13,
		MIX_FRAC_LEN = (1 << MIX_FRAC_BITS),
		MIX_FRAC_MASK = MIX_FRAC_LEN - 1,
	};

	void *pcm_buffer;
	Ref<AudioStreamOpus> base;
	bool active;

protected:
	virtual int _mix_internal(AudioFrame *p_buffer, int p_frames);

public:
	virtual void start(float p_from_pos = 0.f);
	virtual void stop();
	virtual bool is_playing() const;
	virtual int get_loop_count() const;
	virtual void seek(float p_time);
	//virtual void mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames);
	virtual double get_length() const;

	AudioStreamPlaybackOpus();
	~AudioStreamPlaybackOpus();
};

#endif
