/* The particles' object of the letter texts (mail_particles.h). */
#include "mail_particles.h"

#include "autoload_2/heap.h"
#include "clean.h"

static_assert(sizeof(MailTextParticles) == 0x0c, "particles");

/* The Hangul syllables block, U+AC00 to U+D7A3. */
#define HANGUL_FIRST 0xac00
#define HANGUL_LAST 0xd7a3

extern const u8 data_020e3d14[]; /* the particles' object's vtable */

/* func_020a7994: the last Hangul syllable of `characters` (16-bit little-endian characters up
 * to a 0 character), or 0 when it has none. */
void MailParticles_TakeLastSyllable(MailTextParticles *particles, const char *characters)
{
    const u8 *bytes = (const u8 *) characters;

    particles->last_syllable = 0;
    for (int i = 0; bytes[i] != 0 || bytes[i + 1] != 0; i += 2) {
        int character = bytes[i + 1] << 8 | bytes[i];
        if (character >= HANGUL_FIRST && character <= HANGUL_LAST) {
            particles->last_syllable = character;
        }
    }
}
CLEAN_AS(func_020a7994, MailParticles_TakeLastSyllable)

/* func_020a79e0 (slot 1): the object destroyed and freed. */
MailTextParticles *MailParticles_Delete(MailTextParticles *particles)
{
    particles->vtable = data_020e3d14;
    Heap_OperatorDeleteB(particles);
    return particles;
}
CLEAN_AS(func_020a79e0, MailParticles_Delete)

/* func_020a79f8 (slot 0): the destructor: only its vtable set back. */
void MailParticles_Destruct(MailTextParticles *particles)
{
    particles->vtable = data_020e3d14;
}
CLEAN_AS(func_020a79f8, MailParticles_Destruct)

/* func_020a7a04: the constructor: no syllable, "ro" not allowed after a final rieul. */
void MailParticles_Construct(MailTextParticles *particles)
{
    particles->vtable = data_020e3d14;
    particles->last_syllable = 0;
    particles->ro_after_rieul = 0;
}
CLEAN_AS(func_020a7a04, MailParticles_Construct)
