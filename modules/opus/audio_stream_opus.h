#ifndef SEEN_AUDIO_STREAM_OPUS
#define SEEN_AUDIO_STREAM_OPUS

#include "servers/audio/audio_stream.h"

class AudioStreamExample : public AudioStream {
	GDCLASS(AudioStreamExample, AudioStream)	

	friend class AudioStreamPlaybackExample;
	uint64_t pos;
	int mix_rate;
	bool stereo;
	int hz;

protected:
	static void _bind_methods();

public:
	void reset();
	void set_position(uint64_t pos);
	virtual Ref<AudioStreamPlayback> instance_playback() ;
	String get_stream_name() const ;
	void gen_tone(int16_t *pcm_buffer, int size);
	virtual float get_length() const  { return 0.0; }
	AudioStreamExample();
};


#endif
