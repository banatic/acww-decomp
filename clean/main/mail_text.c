/* The letter texts: the requests, loading a message into a text, and the decoder with its tag
 * handlers (mail_text.h). */
#include "mail_text.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "number_text.h"
#include "text_codes.h"
#include "bmg_file.h"
#include "c_library.h"
#include "mail_particles.h"
#include "message_receiver.h"
#include "message_tag.h"
#include "message_walker.h"
#include "text_base.h"
#include "text_walker.h"

static_assert(offsetof(MailTextRequest, message) == 0x1e, "request message");
static_assert(offsetof(MailTextRequest, folder) == 0x20, "request folder");
static_assert(offsetof(MailTextRequest, kind) == 0x24, "request kind");
static_assert(offsetof(MailTextRequest, text) == 0x28, "request text");
static_assert(offsetof(MailTextRequest, first_line) == 0x2c, "request first line");
static_assert(sizeof(MailTextRequest) == 0x30, "request");
static_assert(offsetof(MailTextDecoder, writer) == 0x24, "decoder writer");
static_assert(offsetof(MailTextDecoder, tag) == 0x28, "decoder tag");
static_assert(offsetof(MailTextDecoder, character) == 0x3c, "decoder character");
static_assert(offsetof(MailTextDecoder, ok) == 0x44, "decoder ok");
static_assert(offsetof(MailTextDecoder, convert_next) == 0x45, "decoder convert next");
static_assert(offsetof(MailTextDecoder, return_at) == 0x48, "decoder return at");
static_assert(offsetof(MailTextDecoder, unk_4c) == 0x4c, "decoder 4c");
static_assert(offsetof(MailTextDecoder, count_lines) == 0x50, "decoder count lines");
static_assert(offsetof(MailTextDecoder, characters) == 0x54, "decoder characters");
static_assert(offsetof(MailTextDecoder, newlines) == 0x58, "decoder newlines");
static_assert(sizeof(MailTextDecoder) == MAIL_TEXT_PART_SIZE, "decoder");
static_assert(offsetof(MailTextFile, buffer) == 0xa4, "file buffer");
static_assert(sizeof(MailTextFile) == 0x2a4, "file");
static_assert(sizeof(MailTextParticles) == 0x0c, "particles");
static_assert(offsetof(MailText, file) == 0x05c, "file");
static_assert(offsetof(MailText, particles) == 0x300, "particles");
static_assert(offsetof(MailText, text) == 0x30c, "text");
static_assert(offsetof(MailText, first_line) == 0x50c, "first line");
static_assert(offsetof(MailText, parts) == 0x510, "parts");
static_assert(sizeof(MailText) == 0x904, "letter texts");

#define MAIL_TEXT_PATH_SIZE 0x44
/* The newline, which ends the first line. */
#define MAIL_TEXT_NEWLINE 10
/* The first and last Hangul syllables, and the syllables of one initial and vowel: one for
 * each final consonant, the first with none. */
#define MAIL_TEXT_HANGUL_FIRST 0xac00
#define MAIL_TEXT_HANGUL_LAST 0xd7a3
#define MAIL_TEXT_FINALS 28
#define MAIL_TEXT_FINAL_RIEUL 8
/* The particle "ro" / "euro" (text_codes.h). */
#define MAIL_TEXT_PARTICLE_RO 6

/* The tags' groups that have a handler, and the kinds of their tags. */
#define MAIL_TEXT_GROUP_CODE 0x00
#define MAIL_TEXT_GROUP_PART 0x04
#define MAIL_TEXT_GROUP_FORM 0x0b
#define MAIL_TEXT_CODE_ASTERISK 0
#define MAIL_TEXT_CODE_SLASH 1
#define MAIL_TEXT_CODE_PERCENT 7
#define MAIL_TEXT_CODE_LEFT_BRACE 8
#define MAIL_TEXT_FORM_1 1
#define MAIL_TEXT_FORM_2 2
#define MAIL_TEXT_FORM_CONVERT 3
#define MAIL_TEXT_FORM_4 4
#define MAIL_TEXT_FORM_FIRST_PART 5
#define MAIL_TEXT_FORM_LAST_PART 15
#define MAIL_TEXT_FORM_PARTICLE 0x14
/* Slot 2 of the message file's vtable gives its buffer (MailTextFile_Buffer); slot 3 of a
 * request's its folder, and of a text its characters. */
#define MAIL_TEXT_FILE_BUFFER_SLOT 2
#define MAIL_TEXT_CHARACTERS_SLOT 3

/* The folders and the kinds' folders, by address (NULL for kind 0). */
extern const char *const data_020ca4a0[];
extern const char *const data_020ca4ac[];
extern const char data_020da9c8[]; /* "%s/%s/%s.bmg" */
extern const char data_020da9d8[]; /* "%s/%s.bmg" */

/* The classes: the requests', the decoder's, the walkers' base, the message file's. */
extern const u8 data_020da97c[];
extern const u8 data_020da9ac[];
extern const u8 data_020e3e68[];
extern const u8 data_020da994[];

/* The letter texts. */
extern MailText data_021c69b4;

/* The parts' constructor and destructor, and the arrays'. */
extern void *func_020a8228(void *part);
extern void *func_020a8210(void *part);
extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* The other form of a character (itself when it has none). */
extern int func_02050bdc_unk(int character);

typedef int MailTextObjectFunction(const void *object);
typedef void MailTextDecoderHandler(MailTextDecoder *decoder);

/* A constructor or destructor of the game, as the array functions take it. */
static void (*mail_text_function(void *(*function)(void *) ))(void *)
{
    return (void (*)(void *))(uintptr_t) function;
}

/* What slot `slot` of an object's vtable gives for it. */
static int mail_text_virtual(const void *object, int slot)
{
    const u32 *vtable = *(const u32 *const *) object;
    MailTextObjectFunction *function = (MailTextObjectFunction *) (uintptr_t) vtable[slot];
    return function(object);
}

/* QUIRK: the steps of a load are combined bitwise, so a step that gives a nonzero value
 * without bit 0 still fails it. */
static int mail_text_and(int ok, int result)
{
    return (ok & result) != 0;
}

/* func_0203d4c0 */
int MailTextRequest_FirstLine(const MailTextRequest *request)
{
    return (int) (uintptr_t) request->first_line;
}
CLEAN_AS(func_0203d4c0, MailTextRequest_FirstLine)

/* func_0203d4c4 */
int MailTextRequest_Text(const MailTextRequest *request)
{
    return (int) (uintptr_t) request->text;
}
CLEAN_AS(func_0203d4c4, MailTextRequest_Text)

/* func_0203d4c8 */
void MailTextRequest_SetFirstLine(MailTextRequest *request, s32 *first_line)
{
    request->first_line = first_line;
}
CLEAN_AS(func_0203d4c8, MailTextRequest_SetFirstLine)

/* func_0203d4cc */
void MailTextRequest_SetText(MailTextRequest *request, void *text)
{
    request->text = text;
}
CLEAN_AS(func_0203d4cc, MailTextRequest_SetText)

/* func_0203d4d0 */
void MailTextRequest_SetKind(MailTextRequest *request, int kind)
{
    request->kind = (u32) kind;
}
CLEAN_AS(func_0203d4d0, MailTextRequest_SetKind)

/* func_0203d4d4 */
void MailTextRequest_SetFolder(MailTextRequest *request, int folder)
{
    request->folder = (u32) folder;
}
CLEAN_AS(func_0203d4d4, MailTextRequest_SetFolder)

/* func_0203d4d8: the kind's folder, as an address (0 for kind 0). */
int MailTextRequest_KindFolder(const MailTextRequest *request)
{
    return (int) (uintptr_t) data_020ca4ac[request->kind];
}
CLEAN_AS(func_0203d4d8, MailTextRequest_KindFolder)

/* func_0203d4e8: whether the message is added to the text ("msgb") rather than replacing it. */
int MailTextRequest_Appends(const MailTextRequest *request)
{
    return request->kind == MAIL_TEXT_KIND_MSGB;
}
CLEAN_AS(func_0203d4e8, MailTextRequest_Appends)

/* func_0203d4f8 (slot 3 of the requests' vtable): the folder, as an address. */
unsigned int MailTextRequest_Folder(const MailTextRequest *request)
{
    return (unsigned int) (uintptr_t) data_020ca4a0[request->folder];
}
CLEAN_AS(func_0203d4f8, MailTextRequest_Folder)

/* func_0203d508 (slot 1): the request destroyed and its memory freed. */
MailTextRequest *MailTextRequest_Delete(MailTextRequest *request)
{
    request->vtable = data_020da97c;
    MessageReceiver_DestructBase((MessageReceiver *) request);
    Heap_OperatorDeleteB(request);
    return request;
}
CLEAN_AS(func_0203d508, MailTextRequest_Delete)

/* func_0203d528 (slot 0): the destructor: its vtable, then the base class's destructor. */
MailTextRequest *MailTextRequest_Destruct(MailTextRequest *request)
{
    request->vtable = data_020da97c;
    MessageReceiver_DestructBase((MessageReceiver *) request);
    return request;
}
CLEAN_AS(func_0203d528, MailTextRequest_Destruct)

/* func_0203d540: the constructor: the base class's, then its vtable, folder and kind 0, no
 * text and no first line asked for. */
MailTextRequest *MailTextRequest_Construct(MailTextRequest *request)
{
    MessageReceiver_Construct((MessageReceiver *) request);
    request->vtable = data_020da97c;
    request->folder = 0;
    request->kind = 0;
    request->text = NULL;
    request->first_line = NULL;
    return request;
}
CLEAN_AS(func_0203d540, MailTextRequest_Construct)

/* func_0203d564: the request's message read from its file and decoded into `writer`'s text,
 * which then replaces the request's text (or is added to it, "msgb"); the first line's
 * characters go where the request asks. Nonzero when every step went well. The decoding and
 * the text are left out when the message could not be read. */
int MailText_Load(MailText *writer, MailTextRequest *request)
{
    char path[MAIL_TEXT_PATH_SIZE];
    int kind_folder = MailTextRequest_KindFolder(request);

    if (kind_folder != 0) {
        CLib_SPrintf(path, data_020da9c8, mail_text_virtual(request, MAIL_TEXT_CHARACTERS_SLOT), kind_folder, request->name);
    } else {
        CLib_SPrintf(path, data_020da9d8, mail_text_virtual(request, MAIL_TEXT_CHARACTERS_SLOT), request->name);
    }

    int ok = BmgFile_Open((BmgFile *) &writer->file, path);
    ok = mail_text_and(ok, ok != 0 ? BmgFile_LoadMessage((BmgFile *) &writer->file, &request->message) : 0);
    BmgFile_Close(&writer->file);
    if (ok) {
        void *text = (void *) (uintptr_t) MailTextRequest_Text(request);
        s32 *first_line = (s32 *) (uintptr_t) MailTextRequest_FirstLine(request);
        int appends = MailTextRequest_Appends(request);

        ok = mail_text_and(ok, MailTextDecoder_Decode(&writer->decoder, first_line != NULL));
        if (appends) {
            ok = mail_text_and(ok, TextBase_AppendChars(text, writer->text));
        } else {
            ok = mail_text_and(ok, TextBase_SetChars(text, writer->text));
        }
        if (first_line != NULL) {
            *first_line = writer->first_line;
        }
    }
    return ok;
}
CLEAN_AS(func_0203d564, MailText_Load)

/* func_0203d668: the message file's buffer and the text emptied, no first line measured. */
void MailText_Clear(MailText *writer)
{
    MailTextFile_Clear(&writer->file);
    MI_CpuFill8(writer->text, 0, MAIL_TEXT_SIZE);
    writer->first_line = -1;
}
CLEAN_AS(func_0203d668, MailText_Clear)

/* func_0203d698: the destructor: the parts, the particles' object, the file, the decoder. */
MailText *MailText_Destruct(MailText *writer)
{
    __cxa_vec_cleanup(writer->parts, MAIL_TEXT_PARTS, MAIL_TEXT_PART_SIZE, mail_text_function(func_020a8210));
    MailParticles_Destruct(&writer->particles);
    MailTextFile_Destruct(&writer->file);
    MailTextDecoder_Destruct(&writer->decoder);
    return writer;
}
CLEAN_AS(func_0203d698, MailText_Destruct)

/* func_0203d6d4: the constructor: the decoder (for this object), the file, the particles'
 * object, no first line, the parts, and the text emptied. */
MailText *MailText_Construct(MailText *writer)
{
    MailTextDecoder_Construct(&writer->decoder, writer);
    MailTextFile_Construct(&writer->file);
    MailParticles_Construct(&writer->particles);
    writer->first_line = -1;
    __cxa_vec_ctor(writer->parts, MAIL_TEXT_PARTS, MAIL_TEXT_PART_SIZE, mail_text_function(func_020a8228),
                   mail_text_function(func_020a8210));
    MI_CpuFill8(writer->text, 0, MAIL_TEXT_SIZE);
    return writer;
}
CLEAN_AS(func_0203d6d4, MailText_Construct)

/* func_0203d73c: the particles at the start follow the last Hangul syllable of the text
 * `name` (a 16-bit little-endian character at a time).
 * QUIRK: the scan stops at the first character with a 0 byte, so a Latin letter or digit
 * (high byte 0) ends it; func_020a7994, used for the parts, stops only at a 0 character. */
void MailText_SetParticleName(const void *name)
{
    data_021c69b4.particles.last_syllable = 0;
    const u8 *characters = (const u8 *) (uintptr_t) mail_text_virtual(name, MAIL_TEXT_CHARACTERS_SLOT);
    for (int i = 0; characters[i] != 0 && characters[i + 1] != 0; i += 2) {
        int character = (characters[i + 1] << 8) | characters[i];
        if (character >= MAIL_TEXT_HANGUL_FIRST && character <= MAIL_TEXT_HANGUL_LAST) {
            data_021c69b4.particles.last_syllable = character;
        }
    }
    data_021c69b4.particles.ro_after_rieul = 0;
}
CLEAN_AS(func_0203d73c, MailText_SetParticleName)

/* func_0203d79c: part `index` set to `value` in at most two digits. */
int MailText_SetPartNumber(int index, int value)
{
    return NumberText_SetTwoDigits(data_021c69b4.parts[index], value);
}
CLEAN_AS(func_0203d79c, MailText_SetPartNumber)

/* func_0203d7b0: the same, through the game's second copy of the number setter. */
int MailText_SetPartNumberB(int index, int value)
{
    return NumberText_SetTwoDigitsB(data_021c69b4.parts[index], value);
}
CLEAN_AS(func_0203d7b0, MailText_SetPartNumberB)

/* func_0203d7c4: part `index` set from the text `text`. */
int MailText_SetPartText(int index, const void *text)
{
    return (int) (uintptr_t) TextBase_Copy((TextBase *) (void *) data_021c69b4.parts[index], (TextBase *) text);
}
CLEAN_AS(func_0203d7c4, MailText_SetPartText)

/* func_0203d7d8: message `*message` of "/script/KOR/bbs/<name>.bmg" read into `text`;
 * nonzero when it went well. */
int MailText_LoadBbs(void *text, const unsigned char *message, const char *name)
{
    MailTextRequest request;

    MailTextRequest_Construct(&request);
    MailTextRequest_SetFolder(&request, MAIL_TEXT_FOLDER_BBS);
    MessageReceiver_SetName((MessageReceiver *) &request, name);
    MailTextRequest_SetText(&request, text);
    request.message = *message;
    MailTextRequest_SetKind(&request, MAIL_TEXT_KIND_NONE);
    MailText_Clear(&data_021c69b4);
    int ok = MailText_Load(&data_021c69b4, &request);
    MailTextRequest_Destruct(&request);
    return ok;
}
CLEAN_AS(func_0203d7d8, MailText_LoadBbs)

/* One request of a letter, its text and message set: the kind's file read, the letter texts
 * emptied first. */
static int mail_text_load_kind(MailTextRequest *request, int kind)
{
    MailTextRequest_SetKind(request, kind);
    MailText_Clear(&data_021c69b4);
    return MailText_Load(&data_021c69b4, request);
}

/* func_0203d834: a letter of "/script/KOR/mailz": `super` from "superz" (its first line's
 * characters to `first_line`), `msg` from "msga" with "msgb" added, and `ps` from "psz", each
 * message of the file `name` by its own number. Nonzero when all four went well; all four are
 * loaded either way. */
int MailText_LoadMailz(void *super, void *msg, void *ps, s32 *first_line, const unsigned char *super_message,
                       const unsigned char *msga_message, const unsigned char *msgb_message, const unsigned char *psz_message,
                       const char *name)
{
    MailTextRequest request;

    MailTextRequest_Construct(&request);
    MailTextRequest_SetFolder(&request, MAIL_TEXT_FOLDER_MAILZ);
    MessageReceiver_SetName((MessageReceiver *) &request, name);

    MailTextRequest_SetText(&request, super);
    MailTextRequest_SetFirstLine(&request, first_line);
    request.message = *super_message;
    int super_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_SUPERZ);

    MailTextRequest_SetFirstLine(&request, NULL);
    MailTextRequest_SetText(&request, msg);
    request.message = *msga_message;
    int msga_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_MSGA);

    MailTextRequest_SetText(&request, msg);
    request.message = *msgb_message;
    int msgb_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_MSGB);

    MailTextRequest_SetText(&request, ps);
    request.message = *psz_message;
    int ps_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_PSZ);

    int ok = super_ok && msga_ok && msgb_ok && ps_ok;
    MailTextRequest_Destruct(&request);
    return ok;
}
CLEAN_AS(func_0203d834, MailText_LoadMailz)

/* func_0203d930: a letter of "/script/KOR/mail": `super`, `msg` and `ps` from the kinds of
 * the same names, all from message `*message` of the file `name` (`first_line` gets the
 * characters of the first line of `super`). Nonzero when all three went well; all three are
 * loaded either way. */
int MailText_LoadMail(void *super, void *msg, void *ps, s32 *first_line, const unsigned char *message, const char *name)
{
    MailTextRequest request;

    MailTextRequest_Construct(&request);
    MailTextRequest_SetFolder(&request, MAIL_TEXT_FOLDER_MAIL);
    MessageReceiver_SetName((MessageReceiver *) &request, name);
    request.message = *message;

    MailTextRequest_SetText(&request, super);
    MailTextRequest_SetFirstLine(&request, first_line);
    int super_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_SUPER);

    MailTextRequest_SetFirstLine(&request, NULL);
    MailTextRequest_SetText(&request, msg);
    int msg_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_MSG);

    MailTextRequest_SetText(&request, ps);
    int ps_ok = mail_text_load_kind(&request, MAIL_TEXT_KIND_PS);

    int ok = super_ok && msg_ok && ps_ok;
    MailTextRequest_Destruct(&request);
    return ok;
}
CLEAN_AS(func_0203d930, MailText_LoadMail)

/* func_0203d9f0: tags 0x0b/5 to 0x0b/15 name a part, and nothing is done with it. */
void MailTextDecoder_OnFormPart(MailTextDecoder *decoder, void *part)
{
    (void) decoder;
    (void) part;
}
CLEAN_AS(func_0203d9f0, MailTextDecoder_OnFormPart)

/* func_0203d9f4: tag 0x0b/0x14: particle number (the tag's first byte less 1) walked in place
 * of the tag, in its form after a vowel when the last syllable kept has no final consonant
 * (or there is none), else in its form after a final consonant; with ro_after_rieul set,
 * "ro" after a final rieul takes the form after a vowel.
 * QUIRK: nothing here sets ro_after_rieul, so a final rieul is followed by "euro". */
void MailTextDecoder_InsertParticle(MailTextDecoder *decoder)
{
    u8 particle;
    MessageTag_GetFirstByte(&decoder->tag, &particle);
    particle--;

    const MailTextParticles *particles = &decoder->writer->particles;
    int last = particles->last_syllable;
    TextParticle *text;
    if (last == 0) {
        text = TextCodes_ParticleAfterVowel(particle);
    } else {
        int final = (last - MAIL_TEXT_HANGUL_FIRST) % MAIL_TEXT_FINALS;
        if (final == 0) {
            text = TextCodes_ParticleAfterVowel(particle);
        } else if (particles->ro_after_rieul == 1 && particle == MAIL_TEXT_PARTICLE_RO && final == MAIL_TEXT_FINAL_RIEUL) {
            text = TextCodes_ParticleAfterVowel(particle);
        } else {
            text = TextCodes_ParticleAfterConsonant(particle);
        }
    }
    MessageWalker_Enter((MessageWalker *) decoder, (int) (uintptr_t) text);
}
CLEAN_AS(func_0203d9f4, MailTextDecoder_InsertParticle)

/* func_0203da78: tag 0x0b/4: nothing. */
void MailTextDecoder_OnForm4(void) {}
CLEAN_AS(func_0203da78, MailTextDecoder_OnForm4)

/* func_0203da7c: tag 0x0b/3: the next character is turned into its other form. */
void MailTextDecoder_ConvertNext(MailTextDecoder *decoder)
{
    decoder->convert_next = 1;
}
CLEAN_AS(func_0203da7c, MailTextDecoder_ConvertNext)

/* func_0203da84: tag 0x0b/2. */
void MailTextDecoder_SetForm2(MailTextDecoder *decoder)
{
    decoder->unk_4c = 2;
}
CLEAN_AS(func_0203da84, MailTextDecoder_SetForm2)

/* func_0203da8c: tag 0x0b/1. */
void MailTextDecoder_SetForm1(MailTextDecoder *decoder)
{
    decoder->unk_4c = 1;
}
CLEAN_AS(func_0203da8c, MailTextDecoder_SetForm1)

/* func_0203da94: a tag of group 0x0b, by its kind; other kinds do nothing. */
void MailTextDecoder_OnForm(MailTextDecoder *decoder)
{
    s32 kind = (s32) decoder->tag.kind;

    if (kind == MAIL_TEXT_FORM_1) {
        MailTextDecoder_SetForm1(decoder);
    } else if (kind == MAIL_TEXT_FORM_2) {
        MailTextDecoder_SetForm2(decoder);
    } else if (kind == MAIL_TEXT_FORM_CONVERT) {
        MailTextDecoder_ConvertNext(decoder);
    } else if (kind == MAIL_TEXT_FORM_4) {
        MailTextDecoder_OnForm4();
    } else if (kind >= MAIL_TEXT_FORM_FIRST_PART && kind <= MAIL_TEXT_FORM_LAST_PART) {
        MailTextDecoder_OnFormPart(decoder, decoder->writer->parts[kind - MAIL_TEXT_FORM_FIRST_PART]);
    } else if (kind == MAIL_TEXT_FORM_PARTICLE) {
        MailTextDecoder_InsertParticle(decoder);
    }
}
CLEAN_AS(func_0203da94, MailTextDecoder_OnForm)

/* func_0203daf0: a tag of group 0: one of four one-character texts walked in place of the
 * tag; other kinds do nothing. */
void MailTextDecoder_InsertCode(MailTextDecoder *decoder)
{
    switch ((s32) decoder->tag.kind) {
        case MAIL_TEXT_CODE_ASTERISK:
            MessageWalker_Enter((MessageWalker *) decoder, TextCodes_Asterisk());
            break;
        case MAIL_TEXT_CODE_SLASH:
            MessageWalker_Enter((MessageWalker *) decoder, TextCodes_Slash());
            break;
        case MAIL_TEXT_CODE_PERCENT:
            MessageWalker_Enter((MessageWalker *) decoder, TextCodes_Percent());
            break;
        case MAIL_TEXT_CODE_LEFT_BRACE:
            MessageWalker_Enter((MessageWalker *) decoder, TextCodes_LeftBrace());
            break;
        default:
            break;
    }
}
CLEAN_AS(func_0203daf0, MailTextDecoder_InsertCode)

/* func_0203db44: a tag 4/15-25: the part it names walked in place of the tag, its last Hangul
 * syllable kept for the particles that follow. */
void MailTextDecoder_InsertPart(MailTextDecoder *decoder)
{
    MailText *writer = decoder->writer;
    const void *part = writer->parts[MessageTag_PartIndex(&decoder->tag)];

    MessageWalker_Enter((MessageWalker *) decoder, mail_text_virtual(part, MAIL_TEXT_CHARACTERS_SLOT));
    MailParticles_TakeLastSyllable(&writer->particles,
                                   (const char *) (uintptr_t) mail_text_virtual(part, MAIL_TEXT_CHARACTERS_SLOT));
    writer->particles.ro_after_rieul = 0;
    decoder->unk_4c = 0;
}
CLEAN_AS(func_0203db44, MailTextDecoder_InsertPart)

/* func_0203dba0: the character put in the text (low byte first) while there is room for it
 * and the closing 0; else the decoding fails. While measuring, the characters are counted and
 * the count at the first newline is the first line's length.
 * QUIRK: while measuring, the newlines are left out of the text. */
void MailTextDecoder_PutCharacter(MailTextDecoder *decoder)
{
    MailText *writer = decoder->writer;

    if ((u32) MAIL_TEXT_SIZE - decoder->length <= 2) {
        decoder->ok = 0;
        return;
    }
    if (decoder->character == MAIL_TEXT_NEWLINE && decoder->count_lines != 0) {
        decoder->newlines++;
        if (decoder->newlines == 1) {
            writer->first_line = decoder->characters;
        }
    } else {
        writer->text[decoder->length] = (char) decoder->character;
        writer->text[decoder->length + 1] = (char) (decoder->character >> 8);
        decoder->length += 2;
        if (decoder->count_lines != 0) {
            decoder->characters++;
        }
    }
}
CLEAN_AS(func_0203dba0, MailTextDecoder_PutCharacter)

/* func_0203dc24 (the decoder's slot 6): the walk always goes on, even after a failure. */
int MailTextDecoder_WantsMore(void)
{
    return 1;
}
CLEAN_AS(func_0203dc24, MailTextDecoder_WantsMore)

/* The handler of the tag just read, or NULL when it has none. The ROM picks it as a C++ member
 * pointer from the constants data_020da924, data_020da92c and data_020da934, which name these
 * functions directly (no virtual call, no adjustment). The part test is asked only for group 4. */
static MailTextDecoderHandler *mail_text_handler(MailTextDecoder *decoder)
{
    u32 group = decoder->tag.group;

    if (group == MAIL_TEXT_GROUP_PART && MessageTag_IsPart(&decoder->tag) != 0) {
        return MailTextDecoder_InsertPart;
    }
    if (group == MAIL_TEXT_GROUP_CODE) {
        return MailTextDecoder_InsertCode;
    }
    if (group == MAIL_TEXT_GROUP_FORM) {
        return MailTextDecoder_OnForm;
    }
    return NULL;
}

/* func_0203dc28 (slot 5): the tag at `position` read and handled; a tag without a handler
 * makes the decoding fail. */
void MailTextDecoder_OnTag(MailTextDecoder *decoder, int position)
{
    MessageTag_Read(&decoder->tag, position);
    MailTextDecoderHandler *handler = mail_text_handler(decoder);
    if (handler != NULL) {
        handler(decoder);
    } else {
        decoder->ok = 0;
    }
}
CLEAN_AS(func_0203dc28, MailTextDecoder_OnTag)

/* func_0203dcbc (slot 4): a character of the message, first turned into its other form when a
 * 0x0b/3 tag asked, put in the text; at the position return_at names, the walk goes back to
 * the text it came from. */
void MailTextDecoder_OnCharacter(MailTextDecoder *decoder, int character)
{
    if (decoder->convert_next != 0) {
        decoder->character = func_02050bdc_unk(character);
        decoder->convert_next = 0;
    } else {
        decoder->character = character;
    }
    MailTextDecoder_PutCharacter(decoder);
    if (decoder->base.position == decoder->return_at) {
        decoder->return_at = 0;
        MessageWalker_Return((MessageWalker *) decoder);
    }
}
CLEAN_AS(func_0203dcbc, MailTextDecoder_OnCharacter)

/* func_0203dcfc (slot 3): nothing at the end. */
void MailTextDecoder_OnEnd(void) {}
CLEAN_AS(func_0203dcfc, MailTextDecoder_OnEnd)

/* func_0203dd00 (slot 2): when a text is set: nothing to convert, no position to go back at,
 * 0x4c cleared. */
void MailTextDecoder_OnText(MailTextDecoder *decoder)
{
    decoder->convert_next = 0;
    decoder->return_at = 0;
    decoder->unk_4c = 0;
}
CLEAN_AS(func_0203dd00, MailTextDecoder_OnText)

/* func_0203dd10: the message in the writer's file buffer decoded into its text, measuring the
 * first line when `count_lines` is set; whether it went well. */
unsigned char MailTextDecoder_Decode(MailTextDecoder *decoder, unsigned char count_lines)
{
    decoder->ok = 1;
    decoder->length = 0;
    decoder->count_lines = count_lines;
    decoder->characters = 0;
    decoder->newlines = 0;
    MessageWalker_Reset((MessageWalker *) decoder);
    MessageWalker_Start((MessageWalker *) decoder, mail_text_virtual(&decoder->writer->file, MAIL_TEXT_FILE_BUFFER_SLOT));
    TextWalker_Run((MessageWalker *) decoder, 0);
    return decoder->ok;
}
CLEAN_AS(func_0203dd10, MailTextDecoder_Decode)

/* func_0203dd54 (slot 1): the decoder destroyed and freed. */
MailTextDecoder *MailTextDecoder_Delete(MailTextDecoder *decoder)
{
    decoder->base.vtable = data_020da9ac;
    decoder->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(decoder);
    Heap_OperatorDeleteB(decoder);
    return decoder;
}
CLEAN_AS(func_0203dd54, MailTextDecoder_Delete)

/* func_0203dd7c (slot 0): the destructor: its vtable, the base class's, then the walkers' base
 * destructor. */
MailTextDecoder *MailTextDecoder_Destruct(MailTextDecoder *decoder)
{
    decoder->base.vtable = data_020da9ac;
    decoder->base.vtable = data_020e3e68;
    MessageWalker_BaseDestruct(decoder);
    return decoder;
}
CLEAN_AS(func_0203dd7c, MailTextDecoder_Destruct)

/* func_0203dd9c: the constructor, for `writer`: nothing written, nothing measured, the
 * decoding going well. */
MailTextDecoder *MailTextDecoder_Construct(MailTextDecoder *decoder, MailText *writer)
{
    MessageWalker_Construct((MessageWalker *) decoder);
    decoder->base.vtable = data_020e3e68;
    decoder->base.vtable = data_020da9ac;
    decoder->writer = writer;
    MessageTag_Construct(&decoder->tag);
    decoder->character = 0;
    decoder->length = 0;
    decoder->ok = 1;
    decoder->convert_next = 0;
    decoder->return_at = 0;
    decoder->unk_4c = 0;
    decoder->count_lines = 0;
    decoder->characters = 0;
    decoder->newlines = 0;
    return decoder;
}
CLEAN_AS(func_0203dd9c, MailTextDecoder_Construct)

/* func_0203ddf0 (slot 3 of the file's vtable): the buffer's size. */
int MailTextFile_Size(void)
{
    return MAIL_TEXT_SIZE;
}
CLEAN_AS(func_0203ddf0, MailTextFile_Size)

/* func_0203ddf8 (slot 2): the buffer's address. */
int MailTextFile_Buffer(int file)
{
    return file + (int) offsetof(MailTextFile, buffer);
}
CLEAN_AS(func_0203ddf8, MailTextFile_Buffer)

/* func_0203ddfc: the buffer emptied. */
void MailTextFile_Clear(MailTextFile *file)
{
    MI_CpuFill8(file->buffer, 0, MAIL_TEXT_SIZE);
}
CLEAN_AS(func_0203ddfc, MailTextFile_Clear)

/* func_0203de10 (slot 1): the file destroyed and freed. */
MailTextFile *MailTextFile_Delete(MailTextFile *file)
{
    file->vtable = data_020da994;
    BmgFile_Destruct(file);
    Heap_OperatorDeleteB(file);
    return file;
}
CLEAN_AS(func_0203de10, MailTextFile_Delete)

/* func_0203de30 (slot 0): the destructor: its vtable, then the base class's destructor. */
MailTextFile *MailTextFile_Destruct(MailTextFile *file)
{
    file->vtable = data_020da994;
    BmgFile_Destruct(file);
    return file;
}
CLEAN_AS(func_0203de30, MailTextFile_Destruct)

/* func_0203de48: the constructor: the base class's (with 0), then its vtable. */
MailTextFile *MailTextFile_Construct(MailTextFile *file)
{
    BmgFile_Construct((BmgFile *) file, 0);
    file->vtable = data_020da994;
    return file;
}
CLEAN_AS(func_0203de48, MailTextFile_Construct)
