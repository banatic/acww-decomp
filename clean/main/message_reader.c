/* Main's message reader and its two uses, nicknames and forbidden words (message_reader.h). */
#include "message_reader.h"

#include "autoload_2/heap.h"
#include "clean.h"

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

/* The message receivers' base class: its destructor and constructor, and naming the file. */
extern void func_020a8188(void *receiver);
extern void *func_020a81b8(void *receiver);
extern void func_020a8164(void *receiver, const char *name);

/* The reader's members: the decoder (built for its reader, destroyed; decoding with the two
 * bytes of a request; whether it could), the file (built, destroyed, emptied; opened by path,
 * the message found, closed), the attributes (built, destroyed, reset, copied), the cursor and
 * the line walker. */
extern void *func_020b5418(MessageReader *decoder, MessageReader *reader);
extern void *func_020b53f8(MessageReader *decoder);
extern u8 func_020b5350(MessageReader *decoder, u8 a, u8 b);
extern void *func_020b54c8(void *file);
extern void *func_020b54b0(void *file);
extern void func_020b547c(void *file);
extern u8 func_020a9a08(void *file, const char *path);
extern int func_020a9938(void *file, const u8 *message);
extern void func_020a99d8(void *file);
extern void func_020a9b50(void *attributes);
extern void func_020a9b44(void *attributes);
extern void func_020a9b04(void *attributes);
extern void func_020a9b1c(void *dst, const void *src);
extern void *func_020b4ca4(void *cursor);
extern void *func_020b4c84(void *cursor);
extern void func_020b4c40(void *cursor);               /* back to the start, nothing walked */
extern void func_020b4c28(void *cursor, void *source); /* the text it walks */
extern void func_020b4c24(void *cursor, void *output); /* the text it writes */
extern void func_020b4c0c(void *cursor);               /* back to where it stands */
extern int func_020b4bb4(void *cursor);                /* the next character */
extern void func_020b4bf0(void *cursor, int count);    /* on by `count` characters, matched */
extern void func_020b4bd4(void *cursor);               /* on by one character */
extern void *func_020b4ad4(void *walker);
extern void *func_020b4ab4(void *walker);
extern void func_020a94a4(void *walker);            /* back to its start */
extern void func_020a9354(void *walker, int text);  /* the text it walks */
extern int func_020a92d8(void *walker, int unused); /* a step */
/* The constructors and destructors of the reader's arrays. */
extern void *func_020a8228(void *part);
extern void *func_020a8210(void *part);
extern void *func_020b5524(void *item);
extern void *func_020b550c(void *item);

extern void __cxa_vec_ctor(void *array, int count, int size, void (*construct)(void *), void (*destruct)(void *));
extern void __cxa_vec_cleanup(void *array, int count, int size, void (*destruct)(void *));
extern void MI_CpuFill8(void *dst, u8 value, u32 size);
extern int func_02064328(char *buffer, const char *format, ...); /* sprintf */

/* Texts: the one the filter copies from (a global text object), setting a text from another
 * (func_020a8bb8) or from raw bytes, emptying one, and the line after a line (or NULL). */
extern void *func_020b5548(void);
extern void *func_020a8bb8(void *text, void *source);
extern int func_020a8be4(void *text, const void *data);
extern void func_020a8c1c(void *text);
extern const char *func_020a7bf4(const char *line, int count);
/* What a character may also be written as (the second argument is passed along). */
extern int func_02050bdc_unk(int character, int wanted);

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
    func_020a8188(request);
    Heap_OperatorDeleteB(request);
    return request;
}
CLEAN_AS(func_020b400c, MessageRequest_Delete)

/* func_020b402c: the request's destructor: its vtable, then the base class's. */
MessageRequest *MessageRequest_Destruct(MessageRequest *request)
{
    request->vtable = data_020e5200;
    func_020a8188(request);
    return request;
}
CLEAN_AS(func_020b402c, MessageRequest_Destruct)

/* func_020b4044: the request's constructor: the base class's, then its vtable, folder 0, no
 * text and the decoder's bytes 0. */
MessageRequest *MessageRequest_Construct(MessageRequest *request)
{
    func_020a81b8(request);
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
    func_020b4ab4(reader->line_walker);
    func_020b4c84(reader->cursor);
    __cxa_vec_cleanup(reader->parts, MESSAGE_READER_PARTS, sizeof(reader->parts[0]), message_reader_function(func_020a8210));
    func_020a9b44(reader->attributes);
    func_020b54b0(reader->file);
    func_020b53f8(reader);
    return reader;
}
CLEAN_AS(func_020b4070, MessageReader_Destruct)

/* func_020b40dc: the reader's constructor; the text buffer is cleared last. */
MessageReader *MessageReader_Construct(MessageReader *reader)
{
    func_020b5418(reader, reader);
    func_020b54c8(reader->file);
    func_020a9b50(reader->attributes);
    __cxa_vec_ctor(reader->parts, MESSAGE_READER_PARTS, sizeof(reader->parts[0]), message_reader_function(func_020a8228),
                   message_reader_function(func_020a8210));
    reader->unk_18f0 = 0;
    func_020b4ca4(reader->cursor);
    func_020b4ad4(reader->line_walker);
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
    return func_02050bdc_unk(character, wanted) == wanted;
}
CLEAN_AS(func_020b4178, MessageReader_SameCharacter)

/* func_020b419c: how many characters of the current line (`line`) the text matches where the
 * cursor stands, 0 when it does not match the whole line. The cursor is put back first; the
 * line walker hands the line's characters one by one, up to the end of the line (a newline or
 * 0), each compared with the cursor's next character. */
int MessageReader_MatchLine(MessageReader *reader)
{
    int count = 0;

    func_020b4c0c(reader->cursor);
    func_020a94a4(reader->line_walker);
    func_020a9354(reader->line_walker, (int) (uintptr_t) reader->line);
    for (;;) {
        reader->line_want = 1;
        reader->line_character = 0;
        func_020a92d8(reader->line_walker, 0);
        int wanted = reader->line_character;
        if (wanted == MESSAGE_READER_NEWLINE || wanted == 0) {
            break;
        }
        if (!MessageReader_SameCharacter(func_020b4bb4(reader->cursor), wanted)) {
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

    func_020b4c0c(reader->cursor);
    while (reader->cursor_done == 0) {
        const char *line = reader->text;
        int matched = 0;
        while (line != NULL && (s8) line[0] != MESSAGE_READER_NEWLINE) {
            reader->line = line;
            matched = MessageReader_MatchLine(reader);
            if (matched > 0) {
                break;
            }
            line = func_020a7bf4(line, 1);
        }
        func_020b4c0c(reader->cursor);
        if (matched > 0) {
            func_020b4bf0(reader->cursor, matched);
            found = 1;
        } else {
            func_020b4bd4(reader->cursor);
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
    func_020a8164(&request, data_020e52d0);
    request.message = 0;
    MessageReader_Clear(reader);
    int loaded = MessageReader_Load(&data_021f4dac, &request);
    if (loaded != 0) {
        func_020a8bb8(func_020b5548(), text);
        func_020a8c1c(text);
        func_020b4c40(reader->cursor);
        func_020b4c28(reader->cursor, func_020b5548());
        func_020b4c24(reader->cursor, text);
        reader->line = NULL;
        reader->line_want = 0;
        reader->line_character = 0;
        func_020a94a4(reader->line_walker);
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

    func_02064328(path, data_020e52dc, message_request_folder(request), request->name);
    int ok = func_020a9a08(reader->file, path);
    ok = (ok & (ok != 0 ? func_020a9938(reader->file, &request->message) : 0)) != 0;
    func_020a99d8(reader->file);
    if (ok) {
        void *text = request->text;
        ok = (ok & func_020b5350(reader, request->decode_a, request->decode_b)) != 0;
        if (text != NULL) {
            ok = (ok & func_020a8be4(text, reader->text)) != 0;
            func_020a9b1c((u8 *) text + 8, reader->attributes);
        }
    }
    return ok;
}
CLEAN_AS(func_020b4344, MessageReader_Load)

/* func_020b43f4: the file emptied, the attributes reset and the text buffer cleared. */
void MessageReader_Clear(MessageReader *reader)
{
    func_020b547c(reader->file);
    func_020a9b04(reader->attributes);
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
    func_020a8164(&request, data_020e52e8);
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
