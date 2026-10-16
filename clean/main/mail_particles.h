/* The object that picks the forms of the Korean particles in the letter texts (class
 * data_020e3d14, MailTextParticles in mail_text.h): it keeps the last Hangul syllable of the
 * name or part a particle follows, since the particle's form depends on whether that syllable
 * ends in a consonant. */
#ifndef CLEAN_MAIN_MAIL_PARTICLES_H
#define CLEAN_MAIN_MAIL_PARTICLES_H

#include "mail_text.h"
#include "types.h"

void MailParticles_TakeLastSyllable(MailTextParticles *particles, const char *characters);
MailTextParticles *MailParticles_Delete(MailTextParticles *particles);
void MailParticles_Destruct(MailTextParticles *particles);
void MailParticles_Construct(MailTextParticles *particles);

#endif
