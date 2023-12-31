#ifndef SEEN_AUDIO_STREAM_PLAYBACK_OPUS
#define SEEN_AUDIO_STREAM_PLAYBACK_OPUS

#include "servers/audio/audio_stream.h"

#include "audio_stream_opus.h"

class AudioStreamPlaybackExample : public AudioStreamPlayback {
	GDCLASS(AudioStreamPlaybackExample, AudioStreamPlayback)

	friend class AudioStreamExample;

	enum {
		PCM_BUFFER_SIZE = 4096,
	};

	enum {
		MIX_FRAC_BITS = 13,
		MIX_FRAC_LEN = (1 << MIX_FRAC_BITS),
		MIX_FRAC_MASK = MIX_FRAC_LEN - 1,
	};

	void *pcm_buffer;
	Ref<AudioStreamExample> base;
	bool active;

public:
	virtual void start(float p_from_pos = 0.f) ;
	virtual void stop() ;
	virtual bool is_playing() const ;
	virtual int get_loop_count() const ;
	virtual float get_playback_position() const ;
	virtual void seek(float p_time) ;
	virtual void mix(AudioFrame *p_buffer, float p_rate_scale, int p_frames) ;
	virtual float get_length() const ;

	AudioStreamPlaybackExample();
	~AudioStreamPlaybackExample();
};

#endif
