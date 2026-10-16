/* A sound source (main/sound_emitter.h) kept as a member of an object of overlay 3: the
 * object at 0x310 of the one func_ov003_0221f788 tears down. Overlay 3 lets it go through a
 * function of its own that goes on to main's SoundSource_Release. */
#ifndef CLEAN_OV003_SOUND_SOURCE_MEMBER_H
#define CLEAN_OV003_SOUND_SOURCE_MEMBER_H

#include "main/sound_emitter.h"

void SoundSourceMember_Release(SoundSource *source);

#endif
