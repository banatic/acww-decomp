/* Overlay 3's way to let a member sound source go (sound_source_member.h). */
#include "sound_source_member.h"

#include "clean.h"

/* func_ov003_0221ef3c: SoundSource_Release on `source`. */
void SoundSourceMember_Release(SoundSource *source)
{
    SoundSource_Release(source);
}
CLEAN_AS(func_ov003_0221ef3c, SoundSourceMember_Release)

/* The vtables a member sound source is given while it is constructed: the sound source class's,
 * then its derived class's (autoload_2/sound_source.h). */
extern const u32 data_0213efe8[];
extern const u32 data_0213f004[];

/* func_ov003_0221ef44: the source moved to a copy of `position` (SoundSource_UpdateAt), then
 * asked for sound `number` (SoundSource_Play). */
void SoundSourceMember_PlayAt(SoundSource *source, const Vec3 *position, int number)
{
    Vec3 at = *position;
    SoundSource_UpdateAt(source, &at);
    SoundSource_Play(source, number);
}
CLEAN_AS(func_ov003_0221ef44, SoundSourceMember_PlayAt)

/* func_ov003_0221ef70: SoundSource_Init on `source`. */
void SoundSourceMember_Init(SoundSource *source)
{
    SoundSource_Init(source);
}
CLEAN_AS(func_ov003_0221ef70, SoundSourceMember_Init)

/* func_ov003_0221ef78: the member's destructor, which does nothing. */
void SoundSourceMember_Destruct(SoundSource *source)
{
    (void) source;
}
CLEAN_AS(func_ov003_0221ef78, SoundSourceMember_Destruct)

/* func_ov003_0221ef7c: the member's constructor. Only the vtable is written: first the base
 * class's, then the derived class's, as the C++ constructors run. */
void SoundSourceMember_Construct(SoundSource *source)
{
    source->vtable = (const SoundSourceVtable *) (const void *) data_0213efe8;
    source->vtable = (const SoundSourceVtable *) (const void *) data_0213f004;
}
CLEAN_AS(func_ov003_0221ef7c, SoundSourceMember_Construct)
