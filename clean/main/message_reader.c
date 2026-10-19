/* Main's message reader and its two uses, nicknames and forbidden words (message_reader.h). */
#include "message_reader.h"

#include "autoload_2/heap.h"
#include "clean.h"
#include "bmg_file.h"
#include "c_library.h"
#include "message_attributes.h"
#include "message_cursor.h"
#include "message_decoder.h"
#include "message_query.h"
#include "message_receiver.h"
#include "message_texts.h"
#include "message_walker.h"
#include "text_base.h"
#include "text_walker.h"

static_assert(offsetof(MessageRequest, message) == 0x1e, "message");
static_assert(offsetof(MessageRequest, folder) == 0x20, "folder");
static_assert(offsetof(MessageRequest, decode_b) == 0x29, "decode b");
static_assert(sizeof(MessageRequest) == 0x2c, "request");
static_assert(offsetof(MessageReader, file) == 0x4c, "file");
static_assert(offsetof(MessageReader, attributes) == 0xaf0, "attributes");
static_assert(offsetof(MessageReader, text) == 0xafc, "text");
static_assert(offsetof(MessageReader, parts) == 0x14fc, "parts");
static_assert(offsetof(MessageReader, cursor) == 0x18f4, "cursor");
static_assert(offsetof(MessageReader, cursor_done) == 0x1928, "cursor done");
static_assert(offsetof(MessageReader, line_walker) == 0x1934, "line walker");
static_assert(offsetof(MessageReader, line) == 0x1958, "line");
static_assert(offsetof(MessageReader, items) == 0x1964, "items");
static_assert(sizeof(MessageReader) == 0x1b64, "reader");

#define MESSAGE_READER_PATH_SIZE 0x44
/* The character that ends a line, and a line that starts with it ends the lines. */
#define MESSAGE_READER_NEWLINE 10

extern const u8 data_020e5200[];           /* the requests' vtable */
extern const char *const data_020d208c[2]; /* "/script/KOR/string", "/script/KOR/2d" */
extern const char data_020e52dc[];         /* "%s/%s.bmg" */
extern const char data_020e52d0[];         /* "st_taboo" */
extern const char data_020e52e8[];         /* "st_nickn" */
extern MessageReader data_021f4dac;        /* the reader */
/* A value the decoder reads while a nickname loads, NULL otherwise. */
extern void *data_021f669c;

/* The constructors and destructors of the reader's arrays. */
extern void *func_020a8228(void *part);
extern void *func_020a8210(void *part);
extern void *func_020b5524(void *item);
extern void *func_020b550c(void *item);

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
/* What a character may also be written as (the game's call leaves `wanted` in r1 too, unread). */
extern int func_02050bdc_unk(int character);

typedef int MessageRequestFolderFunction(MessageRequest *request);

static void (*message_reader_function(void *(*function)(void *) ))(void *)
{
    return (void (*)(void *))(uintptr_t) function;
}

/* The request's folder through its vtable (slot 3). */
static const char *message_request_folder(MessageRequest *request)
{
    const u32 *vtable = (const u32 *) request->vtable;
    MessageRequestFolderFunction *folder = (MessageRequestFolderFunction *) (uintptr_t) vtable[3];
    return (const char *) (uintptr_t) folder(request);
}

/* func_020b3ffc (slot 3 of the requests' vtable): the folder's path, as an address. */
int MessageRequest_Folder(MessageRequest *request)
{
    return (int) (uintptr_t) data_020d208c[request->folder];
}
CLEAN_AS(func_020b3ffc, MessageRequest_Folder)

/* func_020b400c: the request destroyed (MessageRequest_Destruct) and its memory freed. */
MessageRequest *MessageRequest_Delete(MessageRequest *request)
{
    request->vtable = data_020e5200;
    MessageReceiver_DestructBase((MessageReceiver *) request);
    Heap_OperatorDeleteB(request);
    return request;
}
CLEAN_AS(func_020b400c, MessageRequest_Delete)

/* func_020b402c: the request's destructor: its vtable, then the base class's. */
MessageRequest *MessageRequest_Destruct(MessageRequest *request)
{
    request->vtable = data_020e5200;
    MessageReceiver_DestructBase((MessageReceiver *) request);
    return request;
}
CLEAN_AS(func_020b402c, MessageRequest_Destruct)

/* func_020b4044: the request's constructor: the base class's, then its vtable, folder 0, no
 * text and the decoder's bytes 0. */
MessageRequest *MessageRequest_Construct(MessageRequest *request)
{
    MessageReceiver_Construct((MessageReceiver *) request);
    request->vtable = data_020e5200;
    request->folder = 0;
    request->text = NULL;
    request->decode_a = 0;
    request->decode_b = 0;
    return request;
}
CLEAN_AS(func_020b4044, MessageRequest_Construct)

/* func_020b4070: the reader's destructor, its members last built first. */
MessageReader *MessageReader_Destruct(MessageReader *reader)
{
    __cxa_vec_cleanup(reader->items, MESSAGE_READER_ITEMS, sizeof(reader->items[0]), message_reader_function(func_020b550c));
    MessageLineWalker_Destruct(reader->line_walker);
    MessageCursor_Destruct(reader->cursor);
    __cxa_vec_cleanup(reader->parts, MESSAGE_READER_PARTS, sizeof(reader->parts[0]), message_reader_function(func_020a8210));
    MessageAttributes_Destruct((MessageAttributes *) (void *) reader->attributes);
    MessageFile_Destruct((MessageFile *) (void *) reader->file);
    MessageDecoder_Destruct((MessageDecoder *) reader);
    return reader;
}
CLEAN_AS(func_020b4070, MessageReader_Destruct)

/* func_020b40dc: the reader's constructor; the text buffer is cleared last. */
MessageReader *MessageReader_Construct(MessageReader *reader)
{
    MessageDecoder_Construct((MessageDecoder *) reader, reader);
    MessageFile_Construct((MessageFile *) (void *) reader->file);
    MessageAttributes_Construct((MessageAttributes *) (void *) reader->attributes);
    __cxa_vec_ctor(reader->parts, MESSAGE_READER_PARTS, sizeof(reader->parts[0]), message_reader_function(func_020a8228),
                   message_reader_function(func_020a8210));
    reader->unk_18f0 = 0;
    MessageCursor_Construct((MessageCursor *) (void *) reader->cursor);
    MessageLineWalker_Construct((MessageLineWalker *) (void *) reader->line_walker);
    __cxa_vec_ctor(reader->items, MESSAGE_READER_ITEMS, sizeof(reader->items[0]), message_reader_function(func_020b5524),
                   message_reader_function(func_020b550c));
    MI_CpuFill8(reader->text, 0, MESSAGE_READER_TEXT_SIZE);
    return reader;
}
CLEAN_AS(func_020b40dc, MessageReader_Construct)

/* func_020b4178: whether `character` matches `wanted`: the same, or the same once
 * func_02050bdc_unk has turned it into its other form (asked only when they differ). */
int MessageReader_SameCharacter(int character, int wanted)
{
    if (character == wanted) {
        return 1;
    }
    return func_02050bdc_unk(character) == wanted;
}
CLEAN_AS(func_020b4178, MessageReader_SameCharacter)

/* func_020b419c: how many characters of the current line (`line`) the text matches where the
 * cursor stands, 0 when it does not match the whole line. The cursor is put back first; the
 * line walker hands the line's characters one by one, up to the end of the line (a newline or
 * 0), each compared with the cursor's next character. */
int MessageReader_MatchLine(MessageReader *reader)
{
    int count = 0;

    MessageCursor_Rewind(reader->cursor);
    MessageWalker_Reset((MessageWalker *) (void *) reader->line_walker);
    MessageWalker_Start((MessageWalker *) (void *) reader->line_walker, (int) (uintptr_t) reader->line);
    for (;;) {
        reader->line_want = 1;
        reader->line_character = 0;
        TextWalker_Run((MessageWalker *) (void *) reader->line_walker, 0);
        int wanted = reader->line_character;
        if (wanted == MESSAGE_READER_NEWLINE || wanted == 0) {
            break;
        }
        if (!MessageReader_SameCharacter(MessageCursor_Read((MessageCursor *) (void *) reader->cursor), wanted)) {
            count = 0;
            break;
        }
        count++;
    }
    return count;
}
CLEAN_AS(func_020b419c, MessageReader_MatchLine)

/* func_020b4218: the cursor's text gone through to its end. At each place the lines of the
 * decoded text are tried in order (up to an empty line or the last); the first that matches
 * moves the cursor on by its length, else the cursor moves on by one character. Whether any
 * line matched. */
int MessageReader_FilterText(MessageReader *reader)
{
    int found = 0;

    MessageCursor_Rewind(reader->cursor);
    while (reader->cursor_done == 0) {
        const char *line = reader->text;
        int matched = 0;
        while (line != NULL && (s8) line[0] != MESSAGE_READER_NEWLINE) {
            reader->line = line;
            matched = MessageReader_MatchLine(reader);
            if (matched > 0) {
                break;
            }
            line = (const char *) (uintptr_t) MessageQuery_Line((int) (uintptr_t) line, 1);
        }
        MessageCursor_Rewind(reader->cursor);
        if (matched > 0) {
            MessageCursor_Mask((MessageCursor *) (void *) reader->cursor, matched);
            found = 1;
        } else {
            MessageCursor_Copy((MessageCursor *) (void *) reader->cursor);
        }
    }
    return found;
}
CLEAN_AS(func_020b4218, MessageReader_FilterText)

/* func_020b42a0: message 0 of "st_taboo" loaded into the global reader (data_021f4dac; it is
 * `reader` that is cleared first); when it loads, `text` is copied into the filter's source
 * text (func_020b5548) and emptied, and `reader`'s cursor set to walk that copy and write into
 * `text`, its line walker reset. Non-NULL when the message loaded (MessageReader_Load's 1). */
void *MessageReader_StartTabooFilter(MessageReader *reader, void *text)
{
    MessageRequest request;

    MessageRequest_Construct(&request);
    MessageReceiver_SetName((MessageReceiver *) &request, data_020e52d0);
    request.message = 0;
    MessageReader_Clear(reader);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    if (loaded != 0) {
        TextBase_Copy((TextBase *) MessageText256_Global(), text);
        TextBase_Clear(text);
        MessageCursor_Reset(reader->cursor);
        MessageCursor_SetSource((MessageCursor *) (void *) reader->cursor, MessageText256_Global());
        MessageCursor_SetOutput((MessageCursor *) (void *) reader->cursor, (int) (uintptr_t) text);
        reader->line = NULL;
        reader->line_want = 0;
        reader->line_character = 0;
        MessageWalker_Reset((MessageWalker *) (void *) reader->line_walker);
    }
    MessageRequest_Destruct(&request);
    return (void *) (uintptr_t) loaded;
}
CLEAN_AS(func_020b42a0, MessageReader_StartTabooFilter)

/* func_020b4344: the request's message read: the file "<folder>/<name>.bmg" opened, the
 * message found in it and the file closed; then the message decoded into the reader's text
 * and, when the request has a text, that text set from it with the attributes. Whether all of
 * it worked; once a step fails the later ones are skipped, except that the request's text is
 * still set once the message was found. */
int MessageReader_Load(MessageReader *reader, MessageRequest *request)
{
    char path[MESSAGE_READER_PATH_SIZE];

    CLib_SPrintf(path, data_020e52dc, message_request_folder(request), request->name);
    int ok = BmgFile_Open((BmgFile *) (void *) reader->file, path);
    ok = (ok & (ok != 0 ? BmgFile_LoadMessage((BmgFile *) (void *) reader->file, &request->message) : 0)) != 0;
    BmgFile_Close(reader->file);
    if (ok) {
        void *text = request->text;
        ok = (ok & MessageDecoder_Decode((MessageDecoder *) reader, request->decode_a, request->decode_b)) != 0;
        if (text != NULL) {
            ok = (ok & TextBase_SetChars(text, reader->text)) != 0;
            MessageAttributes_Copy((MessageAttributes *) (void *) ((u8 *) text + 8),
                                   (const MessageAttributes *) (void *) reader->attributes);
        }
    }
    return ok;
}
CLEAN_AS(func_020b4344, MessageReader_Load)

/* func_020b43f4: the file emptied, the attributes reset and the text buffer cleared. */
void MessageReader_Clear(MessageReader *reader)
{
    MessageFile_Clear((MessageFile *) (void *) reader->file);
    MessageAttributes_Reset((MessageAttributes *) (void *) reader->attributes);
    MI_CpuFill8(reader->text, 0, MESSAGE_READER_TEXT_SIZE);
}
CLEAN_AS(func_020b43f4, MessageReader_Clear)

/* func_020b4424: `text` run through the forbidden words (MessageReader_StartTabooFilter, then
 * MessageReader_FilterText) on the global reader; whether one was found, 0 when "st_taboo"
 * did not load. */
int MessageReader_FilterTaboo(void *text)
{
    if (MessageReader_StartTabooFilter(&data_021f4dac, text) == NULL) {
        return 0;
    }
    return MessageReader_FilterText(&data_021f4dac);
}
CLEAN_AS(func_020b4424, MessageReader_FilterTaboo)

/* func_020b4448: message *message of "st_nickn" read into `text` with the decoder's second
 * byte 1, `context` in data_021f669c while it loads; whether it worked. */
int MessageReader_LoadNickname(void *text, void *context, unsigned char *message)
{
    MessageRequest request;

    MessageRequest_Construct(&request);
    MessageReceiver_SetName((MessageReceiver *) &request, data_020e52e8);
    request.message = *message;
    request.text = text;
    request.decode_b = 1;
    data_021f669c = context;
    MessageReader_Clear(&data_021f4dac);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    data_021f669c = NULL;
    MessageRequest_Destruct(&request);
    return loaded;
}
CLEAN_AS(func_020b4448, MessageReader_LoadNickname)

/* The general messages' numbers in "st_general", by index, and that group's name. */
extern const u8 data_020d2084[];
extern const char data_020e52f4[]; /* "st_general" */
extern const char data_020e5308[]; /* "2d_menu" */
/* The reader's parts (data_021f4dac's at 0x14fc). */
extern u8 data_021f62a8[MESSAGE_READER_PARTS][0x5c];

/* func_020b44d4: general message `index` (data_020d2084) of "st_general" read into `text`,
 * through MessageReader_LoadDecoded when `decoded`, else MessageReader_LoadMessage. */
void MessageReader_LoadGeneral(void *text, int index, int decoded)
{
    u8 message = data_020d2084[index];

    if (decoded != 0) {
        MessageReader_LoadDecoded(text, &message, data_020e52f4);
    } else {
        MessageReader_LoadMessage(text, &message, data_020e52f4);
    }
}
CLEAN_AS(func_020b44d4, MessageReader_LoadGeneral)

/* func_020b496c: the reader's part `index` set from the text `source` (func_020a8bb8). */
void *MessageReader_SetPart(int index, int source)
{
    return TextBase_Copy((TextBase *) (void *) data_021f62a8[index], (void *) (uintptr_t) source);
}
CLEAN_AS(func_020b496c, MessageReader_SetPart)

/* func_020b4980: message *message of the file `name` ("2d_menu" for NULL) in
 * "/script/KOR/2d" read into `text` by the global reader; whether it worked. */
int MessageReader_LoadMenuMessage(void *text, unsigned char *message, const char *name)
{
    MessageRequest request;

    if (name == NULL) {
        name = data_020e5308;
    }
    MessageRequest_Construct(&request);
    request.folder = 1;
    MessageReceiver_SetName((MessageReceiver *) &request, name);
    request.message = *message;
    request.text = text;
    MessageReader_Clear(&data_021f4dac);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    MessageRequest_Destruct(&request);
    return loaded;
}
CLEAN_AS(func_020b4980, MessageReader_LoadMenuMessage)

/* func_020b49d4: as MessageReader_LoadMessage with the decoder's first byte 1, so that the
 * message's 0xff/2 tags are decoded into the text rather than kept (MessageDecoder_CopyTag). */
void *MessageReader_LoadDecoded(void *text, unsigned char *message, const char *name)
{
    MessageRequest request;

    MessageRequest_Construct(&request);
    MessageReceiver_SetName((MessageReceiver *) &request, name);
    request.message = *message;
    request.text = text;
    request.decode_a = 1;
    MessageReader_Clear(&data_021f4dac);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    MessageRequest_Destruct(&request);
    return (void *) (uintptr_t) loaded;
}
CLEAN_AS(func_020b49d4, MessageReader_LoadDecoded)

/* func_020b4a20: message *message of the file `name` in "/script/KOR/string" read into
 * `text` by the global reader; whether it worked. */
int MessageReader_LoadMessage(void *text, unsigned char *message, const char *name)
{
    MessageRequest request;

    MessageRequest_Construct(&request);
    MessageReceiver_SetName((MessageReceiver *) &request, name);
    request.message = *message;
    request.text = text;
    MessageReader_Clear(&data_021f4dac);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    MessageRequest_Destruct(&request);
    return loaded;
}
CLEAN_AS(func_020b4a20, MessageReader_LoadMessage)
