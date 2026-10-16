/* The speaking voice (voice.h). */
#include "voice.h"

#include <stddef.h>

#include "clean.h"

/* The sound system (the only SoundSystem the game has). */
extern SoundSystem data_021fd1bc;
/* Where the intonation pattern is: 0 to 15, back to 0 after 15. */
extern u8 data_021fd1b0;
/* Pattern 2's rise, flipped each time it starts over. */
extern u8 data_021fd1ac;
/* Spaces voiced since the pattern last started over because of them. */
extern u8 data_021fd1a8;
/* The last `ch2` and `ch` that were not a lengthening mark (Voice_Speak). */
extern u16 data_021fd1b4;
extern u16 data_021fd1b8;
/* The vowel sample (1 to 5) of each sample: a lengthening mark repeats the last vowel. */
extern const u8 data_0213e85c[];

extern void OS_Terminate(void);
/* Sound effect `number` played on the sound system, unless it is muted. */
extern void func_020f1fb4(SoundSystem *system, int number);
/* Voice sequence `number` played at `volume` (0 to 0x7f) and `pitch`, adjusted per voice kind. */
extern void func_020f1da4(SoundSystem *system, int number, int volume, int pitch);

/* The characters the voice treats apart (UTF-16). */
enum {
    CH_NEWLINE = 0x000a,
    CH_SPACE = 0x0020,
    CH_MIDDLE_DOT = 0x30fb,  /* katakana middle dot: a sound effect instead of the voice */
    CH_LONG_MARK = 0x30fc,   /* katakana prolonged sound mark */
    CH_EXCLAMATION = 0xff01, /* fullwidth '!' */
    CH_COMMA = 0xff0c,       /* fullwidth ',' */
    CH_QUESTION = 0xff1f,    /* fullwidth '?' */
    CH_WAVE = 0xff5e,        /* fullwidth tilde: a lengthening mark too */
    HANGUL_FIRST = 0xac00,
    HANGUL_LAST = 0xd7a3,
};

/* The sound effect for the middle dot and for Voice_Speak's action 1. */
#define EFFECT_TICK 0x2c

/* Voice_Speak's actions. */
enum {
    VOICE_CHARACTER = 0,
    VOICE_TICK = 1,
    VOICE_NOTHING = 2,
};

/* Hangul syllables are HANGUL_FIRST + (initial * 21 + medial) * 28 + final. */
#define MEDIALS 21
#define FINALS 28

/* A syllable's pitch offset (before -0x40) and volume. */
typedef struct Tone {
    s16 pitch;
    u8 volume;
} Tone;

/* What a pattern does not set. */
static const Tone TONE_FLAT = {0, 0x7f};

static const Tone PATTERN_0[4] = {{-0x40, 0x50}, {0x80, 0x6e}, {0x40, 0x64}, {0x40, 0x69}};

static const Tone PATTERN_1[16] = {
    {0xf0, 0x7d}, {0xb4, 0x6e}, {0x96, 0x5a}, {-0x4d, 0x69}, {0xbe, 0x7d}, {0x78, 0x6e}, {0x5a, 0x5a}, {-0x4d, 0x69},
    {0xf0, 0x7d}, {0xb4, 0x6e}, {0x96, 0x5a}, {-0x4d, 0x69}, {0xbe, 0x7d}, {0x78, 0x6e}, {0x5a, 0x5a}, {-0x4d, 0x69},
};
static const Tone PATTERN_1_LATER = {-0x4d, 0x69};

static const Tone PATTERN_3[16] = {
    {0x5a, 0x69}, {0x1e, 0x5a}, {0, 0x46}, {-0xe3, 0x55}, {0x28, 0x69}, {-0x1e, 0x5a}, {-0x3c, 0x46}, {-0xe3, 0x55},
    {0x5a, 0x69}, {0x1e, 0x5a}, {0, 0x46}, {-0xe3, 0x55}, {0x28, 0x69}, {-0x1e, 0x5a}, {-0x3c, 0x46}, {-0xe3, 0x55},
};
static const Tone PATTERN_3_LATER = {-0xe3, 0x55};

static const Tone PATTERN_4[16] = {
    {0x80, 0x4b},  {0x100, 0x5f}, {0x1c0, 0x7d}, {0x140, 0x69}, {0xc0, 0x55}, {0x80, 0x4b},  {0x40, 0x41}, {0x80, 0x4b},
    {0x1c0, 0x7d}, {0x140, 0x69}, {0xc0, 0x55},  {0x40, 0x41},  {0x80, 0x4b}, {0x140, 0x69}, {0x80, 0x4b}, {0x140, 0x69},
};

/* The pattern's tone at `step`, or `later` past the table. */
static Tone tone_at(const Tone *table, unsigned size, unsigned step, Tone later)
{
    return step < size ? table[step] : later;
}

static int is_syllable(unsigned ch)
{
    return ch >= HANGUL_FIRST && ch <= HANGUL_LAST;
}

/* The voice sequence of a syllable. */
static int sequence_of(SoundSystem *system, unsigned ch)
{
    return Voice_SequenceOfSample(system, (u16) Voice_SampleOfSyllable(system, ch));
}

/* The sequence of a mark voiced after what came before: the last syllable passed as `ch2`,
 * else the vowel of the last `ch`. */
static int sequence_of_last(SoundSystem *system)
{
    if (is_syllable(data_021fd1b4)) {
        return sequence_of(system, data_021fd1b4);
    }
    return Voice_SequenceOfSample(system, data_0213e85c[(u16) Voice_SampleOfSyllable(system, data_021fd1b8)]);
}

static int is_long_mark(unsigned ch)
{
    return ch == CH_LONG_MARK || ch == CH_WAVE;
}

/* func_020efc74: the voice's work for a character of text. Action 0 voices `ch`, along
 * the intonation `pattern` (0 to 4), `ch2` also being looked at (which character the game
 * passes there is not established: a '?' in it raises the pitch, a ',' or a new line lowers it);
 * a middle dot in either plays a sound effect instead. Action 1 plays that sound effect, 2 and
 * others do nothing. The game stops for a voice of kind 5.
 *
 * A space, a new line or a comma is voiced as the syllable `ch2` when it is one, else as the
 * last one, else not at all (sequence 0); '?', '!' and the lengthening marks repeat the last
 * syllable, or the last character's vowel. Patterns 2 and 4 start over after two spaces, the
 * others after one; '?', '!' and a new line make them start over too. */
void Voice_Speak(SoundSystem *system, int action, int pattern, unsigned short ch, unsigned short ch2)
{
    if (system->voice_type == 5) {
        OS_Terminate();
    }

    switch (action) {
        case VOICE_CHARACTER:
            if (ch == CH_MIDDLE_DOT || ch2 == CH_MIDDLE_DOT) {
                func_020f1fb4(&data_021fd1bc, EFFECT_TICK);
            } else {
                unsigned step = data_021fd1b0;
                int spaces_to_restart = 0;
                Tone tone = TONE_FLAT;
                int sequence = 0;

                switch (pattern) {
                    case 0:
                        spaces_to_restart = 1;
                        tone = tone_at(PATTERN_0, 4, step, TONE_FLAT);
                        break;
                    case 1:
                        spaces_to_restart = 1;
                        tone = tone_at(PATTERN_1, 16, step, PATTERN_1_LATER);
                        break;
                    case 2:
                        /* A falling line, starting higher every other time. */
                        spaces_to_restart = 2;
                        if (step == 0) {
                            data_021fd1ac = data_021fd1ac == 0;
                        }
                        if (data_021fd1ac == 0) {
                            tone.pitch = (s16) (0 - (int) (step * 0x11));
                            tone.volume = (u8) (0x64 - step * 3);
                        } else {
                            tone.pitch = (s16) (0x4d - (int) (step * 0x11));
                            tone.volume = (u8) (0x73 - step * 3);
                        }
                        break;
                    case 3:
                        spaces_to_restart = 1;
                        tone = tone_at(PATTERN_3, 16, step, PATTERN_3_LATER);
                        break;
                    case 4:
                        spaces_to_restart = 2;
                        tone = tone_at(PATTERN_4, 16, step, TONE_FLAT);
                        break;
                }

                switch (ch2) {
                    case CH_EXCLAMATION:
                        tone.pitch = 0x100;
                        tone.volume = 0x7f;
                        break;
                    case CH_NEWLINE:
                    case CH_COMMA:
                        tone.pitch = -0x40;
                        tone.volume = 0x5a;
                        break;
                    case CH_QUESTION:
                        tone.pitch = 0x180;
                        tone.volume = 0x6e;
                        break;
                }

                switch (ch) {
                    default:
                        sequence = sequence_of(system, ch);
                        break;
                    case CH_SPACE:
                    case CH_NEWLINE:
                    case CH_COMMA:
                        if (is_syllable(ch2)) {
                            sequence = sequence_of(system, ch2);
                        } else if (is_syllable(data_021fd1b4)) {
                            sequence = sequence_of(system, data_021fd1b4);
                        }
                        break;
                    case CH_QUESTION:
                        tone.pitch = 0x180;
                        tone.volume = 0x6e;
                        sequence = sequence_of_last(system);
                        break;
                    case CH_EXCLAMATION:
                        tone.pitch = 0x100;
                        tone.volume = 0x7f;
                        sequence = sequence_of_last(system);
                        break;
                    case CH_LONG_MARK:
                    case CH_WAVE:
                        sequence = sequence_of_last(system);
                        break;
                }

                func_020f1da4(system, sequence, Voice_ClampVolume(system, tone.volume), tone.pitch - 0x40);

                data_021fd1b0++;
                if (data_021fd1b0 > 15) {
                    data_021fd1b0 = 0;
                }
                if (ch == CH_QUESTION || ch == CH_EXCLAMATION || ch == CH_NEWLINE || ch2 == CH_QUESTION ||
                    ch2 == CH_EXCLAMATION || ch2 == CH_NEWLINE) {
                    data_021fd1b0 = 0;
                }
                if (ch == CH_SPACE || ch2 == CH_SPACE) {
                    if (data_021fd1a8 == spaces_to_restart) {
                        data_021fd1a8 = 0;
                        data_021fd1b0 = 0;
                    } else {
                        data_021fd1a8++;
                    }
                }
            }
            if (!is_long_mark(ch)) {
                data_021fd1b8 = ch;
            }
            if (!is_long_mark(ch2)) {
                data_021fd1b4 = ch2;
            }
            break;
        case VOICE_TICK:
            func_020f1fb4(&data_021fd1bc, EFFECT_TICK);
            break;
        case VOICE_NOTHING:
            break;
    }
}
CLEAN_AS(func_020efc74, Voice_Speak)

/* The vowel classes of the 21 Hangul medials, by the kana vowel they are voiced with. */
enum { V_A, V_I, V_U, V_E, V_O };

static const u8 MEDIAL_VOWEL[MEDIALS] = {
    V_A, V_A, V_A, V_E, V_O, V_E, V_O, V_E, V_O, V_A, V_E, /* a ae ya yae eo e yeo ye o wa wae */
    V_E, V_O, V_U, V_O, V_E, V_I, V_U, V_U, V_I, V_I,      /* oe yo u wo we wi yu eu ui i */
};

/* The samples of each of the 19 initials, by vowel class (a i u e o). */
static const u8 INITIAL_ROW[19][5] = {
    {0x2e, 0x2f, 0x30, 0x31, 0x32}, /* g: ga row */
    {0x06, 0x07, 0x08, 0x09, 0x0a}, /* kk: ka row */
    {0x15, 0x16, 0x17, 0x18, 0x19}, /* n: na row */
    {0x38, 0x34, 0x35, 0x39, 0x3a}, /* d: da, ji, zu, de, do */
    {0x10, 0x11, 0x12, 0x13, 0x14}, /* tt: ta row */
    {0x27, 0x28, 0x29, 0x2a, 0x2b}, /* r: ra row */
    {0x1f, 0x20, 0x21, 0x22, 0x23}, /* m: ma row */
    {0x3b, 0x3c, 0x3d, 0x3e, 0x3f}, /* b: ba row */
    {0x40, 0x41, 0x42, 0x43, 0x44}, /* pp: pa row */
    {0x0b, 0x0c, 0x0d, 0x0e, 0x0f}, /* s: sa row */
    {0x0b, 0x0c, 0x0d, 0x0e, 0x0f}, /* ss: sa row */
    {0x01, 0x02, 0x03, 0x04, 0x05}, /* silent: the vowels */
    {0x33, 0x34, 0x35, 0x36, 0x37}, /* j: za row */
    {0x10, 0x11, 0x12, 0x13, 0x14}, /* jj: ta row */
    {0x10, 0x11, 0x12, 0x13, 0x14}, /* ch: ta row */
    {0x06, 0x07, 0x08, 0x09, 0x0a}, /* k: ka row */
    {0x10, 0x11, 0x12, 0x13, 0x14}, /* t: ta row */
    {0x40, 0x41, 0x42, 0x43, 0x44}, /* p: pa row */
    {0x1a, 0x1b, 0x1c, 0x1d, 0x1e}, /* h: ha row */
};

#define INITIAL_SILENT 11

/* func_020f0444: the voice sample (1 to 0x44) of a Hangul syllable, by its initial consonant
 * and its vowel; 0 for any other character. A silent initial gives the vowel, with ya, yo, yu
 * and wa voiced as such.
 * QUIRK: the original tests the jamo ieung (0x3147) apart, to give the same 0. */
int Voice_SampleOfSyllable(SoundSystem *system, int ch)
{
    int initial;
    int medial;

    (void) system;
    if (!is_syllable((unsigned) ch)) {
        return 0;
    }
    initial = (ch - HANGUL_FIRST) / (MEDIALS * FINALS);
    medial = (ch - HANGUL_FIRST) % (MEDIALS * FINALS) / FINALS;
    if (initial == INITIAL_SILENT) {
        switch (medial) {
            case 2: /* ya */
                return 0x24;
            case 17: /* yu */
                return 0x25;
            case 12: /* yo */
                return 0x26;
            case 9: /* wa */
                return 0x2c;
        }
    }
    return INITIAL_ROW[initial][MEDIAL_VOWEL[medial]];
}
CLEAN_AS(func_020f0444, Voice_SampleOfSyllable)

/* func_020f0ccc: the voice sequence of a sample for the system's voice kind: kinds 0 and 4,
 * 1 and 3, and 2 have their own blocks; sample 0 stays 0 (silence), and an unknown kind keeps
 * the sample's number.
 * QUIRK: the sum is cut to 16 bits. */
int Voice_SequenceOfSample(SoundSystem *system, unsigned short sample)
{
    if (sample == 0) {
        return 0;
    }
    switch (system->voice_type) {
        case 0:
        case 4:
            return (u16) (sample + 0xce);
        case 1:
        case 3:
            return (u16) (sample + 0x140);
        case 2:
            return (u16) (sample + 0x1b2);
    }
    return sample;
}
CLEAN_AS(func_020f0ccc, Voice_SequenceOfSample)

/* func_020f0d40: a volume kept at 0x7f at most. */
int Voice_ClampVolume(SoundSystem *system, unsigned volume)
{
    (void) system;
    return volume > 0x7f ? 0x7f : (int) volume;
}
CLEAN_AS(func_020f0d40, Voice_ClampVolume)
