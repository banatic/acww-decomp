/* Overlay 3's way to let a member sound source go (sound_source_member.h). */
#include "sound_source_member.h"

#include "clean.h"

/* func_ov003_0221ef3c: SoundSource_Release on `source`. */
void SoundSourceMember_Release(SoundSource *source)
{
    SoundSource_Release(source);
}
CLEAN_AS(func_ov003_0221ef3c, SoundSourceMember_Release)
