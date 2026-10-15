/* func_020a9a08 @ 0x020a9a08, 0x36 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char *strncpy(void *dest, const void *src, unsigned int size);
extern int FS_OpenFile(const void *a, const void *b);

typedef struct {
    unsigned char pad_00[5];
    unsigned char data[62];
    unsigned char pad_43;
    unsigned char unk_44[4];
    unsigned char pad_48[68];
    unsigned char flag;
} UnkStruct_020a9a08;

unsigned char func_020a9a08(UnkStruct_020a9a08 *s, const void *src)
{
    unsigned char result;

    strncpy(s->data, src, 0x3E);
    if (FS_OpenFile(s->unk_44, src) != 0) {
        result = 1;
    } else {
        result = 0;
    }
    s->flag = result;
    return s->flag;
}
