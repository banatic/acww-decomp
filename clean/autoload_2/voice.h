/* The speaking voice: as text is shown, each Hangul syllable is voiced by a short sample chosen
 * from its initial consonant and its vowel. The samples are numbered 1 to 0x44 in an order that
 * follows the Japanese kana table (1-5 the vowels a i u e o, then rows of five: k, s, t, n, h,
 * m, then ya yu yo, r, wa, ga, z, d, b, p), each voice kind having its own block of sequences.
 * The pitch and volume of successive syllables follow an intonation pattern, moved by the
 * punctuation around them. */
#ifndef CLEAN_AUTOLOAD_2_VOICE_H
#define CLEAN_AUTOLOAD_2_VOICE_H

#include "sound.h"
#include "types.h"

void Voice_Speak(SoundSystem *system, int action, int pattern, unsigned short ch, unsigned short ch2);
int Voice_SampleOfSyllable(SoundSystem *system, int ch);
int Voice_SequenceOfSample(SoundSystem *system, unsigned short sample);
int Voice_ClampVolume(SoundSystem *system, unsigned volume);

#endif
