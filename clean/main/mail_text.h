/* The letter texts (data_021c69b4, built by a static constructor and destroyed at exit): the
 * texts of letters and of the notice board are read from message files under one of three
 * folders, "/script/KOR/mail", "/script/KOR/mailz" and "/script/KOR/bbs", and decoded into a
 * text of 0x200 bytes, which then goes to (or is added to) the caller's text.
 *
 * A request (MailTextRequest) names the file ("<folder>/<kind>/<name>.bmg", or
 * "<folder>/<name>.bmg" for kind 0), the message's number in it, the text to fill and, when it
 * asks for one, where to put the number of characters of the decoded text's first line.
 *
 * The decoder (MailTextDecoder) walks the message (message_cursor.h) and acts on its tags:
 *
 * - 0/0, 0/1, 0/7, 0/8: one of the texts "*", "/", "%" and "{" walked in place of the tag;
 * - 4/15 to 4/25: one of the eleven parts (MailText_SetPartText and the number setters fill
 *   them) walked in place of the tag; its last Hangul syllable is kept for the particles;
 * - 0x0b/3: the next character is first turned into its other form (func_02050bdc_unk);
 * - 0x0b/0x14: a particle (its number is the tag's first byte less 1) in the form that follows
 *   the last Hangul syllable kept: after a vowel or after a final consonant (text_codes.h);
 * - 0x0b/1 and 0x0b/2 set a value nothing here reads, 0x0b/4 to 0x0b/15 do nothing.
 *
 * A tag of another group makes the decoding fail, and so does a full text; the walk goes on to
 * the end either way. */
#ifndef CLEAN_MAIN_MAIL_TEXT_H
#define CLEAN_MAIN_MAIL_TEXT_H

#include "message_decoder.h"
#include "types.h"

#define MAIL_TEXT_SIZE 0x200
#define MAIL_TEXT_PARTS 11
#define MAIL_TEXT_PART_SIZE 0x5c

/* The folders a request reads from (data_020ca4a0). */
enum MailTextFolder {
    MAIL_TEXT_FOLDER_MAIL = 0,  /* "/script/KOR/mail" */
    MAIL_TEXT_FOLDER_MAILZ = 1, /* "/script/KOR/mailz" */
    MAIL_TEXT_FOLDER_BBS = 2    /* "/script/KOR/bbs" */
};

/* The kinds of a request: the folder under the request's folder (data_020ca4ac). */
enum MailTextKind {
    MAIL_TEXT_KIND_NONE = 0,   /* no folder */
    MAIL_TEXT_KIND_SUPER = 1,  /* "super" */
    MAIL_TEXT_KIND_MSG = 2,    /* "msg" */
    MAIL_TEXT_KIND_PS = 3,     /* "ps" */
    MAIL_TEXT_KIND_SUPERZ = 4, /* "superz" */
    MAIL_TEXT_KIND_MSGA = 5,   /* "msga" */
    MAIL_TEXT_KIND_MSGB = 6,   /* "msgb": added to the text instead of replacing it */
    MAIL_TEXT_KIND_PSZ = 7     /* "psz" */
};

struct MailText;

/* What to read (0x30 bytes, class data_020da97c): a message receiver (the class of
 * data_020e3d4c) with fields of its own. */
typedef struct MailTextRequest {
    const void *vtable; /* 0x00: slot 3 gives the folder (MailTextRequest_Folder) */
    char name[26];      /* 0x04: the file's name */
    u8 message;         /* 0x1e: the message's number in it */
    u8 unk_1f;
    u32 folder;      /* 0x20: enum MailTextFolder */
    u32 kind;        /* 0x24: enum MailTextKind */
    void *text;      /* 0x28: the text the message goes to */
    s32 *first_line; /* 0x2c: where the first line's length goes, or NULL */
} MailTextRequest;

/* The decoder (0x5c bytes, class data_020da9ac). */
typedef struct MailTextDecoder {
    MessageWalker base;
    struct MailText *writer; /* 0x24: the letter texts it writes into */
    MessageTag tag;          /* 0x28: the tag being handled */
    s32 character;           /* 0x3c: the character being put in the text */
    u32 length;              /* 0x40: the bytes of the text written so far */
    u8 ok;                   /* 0x44: cleared when a step fails */
    u8 convert_next;         /* 0x45: turn the next character into its other form */
    u8 unk_46[2];
    u32 return_at;  /* 0x48: a position at which the walk goes back to the text it came
                         * from (0: none); nothing here sets it */
    s32 unk_4c;     /* 0x4c: 1 or 2 from tags 0x0b/1 and 0x0b/2, 0 at a part */
    u8 count_lines; /* 0x50: measure the first line (the request asked for it) */
    u8 unk_51[3];   /* 0x51 */
    s32 characters; /* 0x54: the characters written, while measuring */
    s32 newlines;   /* 0x58: the newlines met, while measuring */
} MailTextDecoder;

/* The message file (0x2a4 bytes, class data_020da994): a file (the base class of
 * data_020e3d34, func_020a9a90 builds it) with a buffer of 0x200 bytes a message is read
 * into. */
typedef struct MailTextFile {
    const void *vtable;
    u8 base_04[0xa0];
    u8 buffer[MAIL_TEXT_SIZE]; /* 0xa4 */
} MailTextFile;

/* What the particles follow (0x0c bytes, class data_020e3d14). */
typedef struct MailTextParticles {
    const void *vtable;
    s32 last_syllable;  /* 0x04: the last Hangul syllable of the name or part, 0 for none */
    s32 ro_after_rieul; /* 0x08: 1 lets particle 6 ("ro") follow a final rieul in its
                         * after-vowel form */
} MailTextParticles;

/* The letter texts (0x904 bytes). */
typedef struct MailText {
    MailTextDecoder decoder;                        /* 0x000: decodes for this object */
    MailTextFile file;                              /* 0x05c */
    MailTextParticles particles;                    /* 0x300 */
    char text[MAIL_TEXT_SIZE];                      /* 0x30c: the decoded text */
    s32 first_line;                                 /* 0x50c: its first line's characters, -1 */
    u8 parts[MAIL_TEXT_PARTS][MAIL_TEXT_PART_SIZE]; /* 0x510: texts the tags 4/15-25 insert */
} MailText;

int MailTextRequest_FirstLine(const MailTextRequest *request);
int MailTextRequest_Text(const MailTextRequest *request);
void MailTextRequest_SetFirstLine(MailTextRequest *request, s32 *first_line);
void MailTextRequest_SetText(MailTextRequest *request, void *text);
void MailTextRequest_SetKind(MailTextRequest *request, int kind);
void MailTextRequest_SetFolder(MailTextRequest *request, int folder);
int MailTextRequest_KindFolder(const MailTextRequest *request);
int MailTextRequest_Appends(const MailTextRequest *request);
unsigned int MailTextRequest_Folder(const MailTextRequest *request);
MailTextRequest *MailTextRequest_Delete(MailTextRequest *request);
MailTextRequest *MailTextRequest_Destruct(MailTextRequest *request);
MailTextRequest *MailTextRequest_Construct(MailTextRequest *request);

int MailText_Load(MailText *writer, MailTextRequest *request);
void MailText_Clear(MailText *writer);
MailText *MailText_Destruct(MailText *writer);
MailText *MailText_Construct(MailText *writer);
void MailText_SetParticleName(const void *name);
int MailText_SetPartNumber(int index, int value);
int MailText_SetPartNumberB(int index, int value);
int MailText_SetPartText(int index, const void *text);
int MailText_LoadBbs(void *text, const unsigned char *message, const char *name);
int MailText_LoadMailz(void *super, void *msg, void *ps, s32 *first_line, const unsigned char *super_message,
                       const unsigned char *msga_message, const unsigned char *msgb_message, const unsigned char *psz_message,
                       const char *name);
int MailText_LoadMail(void *super, void *msg, void *ps, s32 *first_line, const unsigned char *message, const char *name);

void MailTextDecoder_OnFormPart(MailTextDecoder *decoder, void *part);
void MailTextDecoder_InsertParticle(MailTextDecoder *decoder);
void MailTextDecoder_OnForm4(void);
void MailTextDecoder_ConvertNext(MailTextDecoder *decoder);
void MailTextDecoder_SetForm2(MailTextDecoder *decoder);
void MailTextDecoder_SetForm1(MailTextDecoder *decoder);
void MailTextDecoder_OnForm(MailTextDecoder *decoder);
void MailTextDecoder_InsertCode(MailTextDecoder *decoder);
void MailTextDecoder_InsertPart(MailTextDecoder *decoder);
void MailTextDecoder_PutCharacter(MailTextDecoder *decoder);
int MailTextDecoder_WantsMore(void);
void MailTextDecoder_OnTag(MailTextDecoder *decoder, int position);
void MailTextDecoder_OnCharacter(MailTextDecoder *decoder, int character);
void MailTextDecoder_OnEnd(void);
void MailTextDecoder_OnText(MailTextDecoder *decoder);
unsigned char MailTextDecoder_Decode(MailTextDecoder *decoder, unsigned char count_lines);
MailTextDecoder *MailTextDecoder_Delete(MailTextDecoder *decoder);
MailTextDecoder *MailTextDecoder_Destruct(MailTextDecoder *decoder);
MailTextDecoder *MailTextDecoder_Construct(MailTextDecoder *decoder, MailText *writer);

int MailTextFile_Size(void);
int MailTextFile_Buffer(int file);
void MailTextFile_Clear(MailTextFile *file);
MailTextFile *MailTextFile_Delete(MailTextFile *file);
MailTextFile *MailTextFile_Destruct(MailTextFile *file);
MailTextFile *MailTextFile_Construct(MailTextFile *file);

#endif
