/* func_0201f2b8 @ 0x0201f2b8, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0201f2b8_3 {
    char pad_00[0x830];
    int unk_830;
} UnkStruct_0201f2b8_3;

typedef struct UnkStruct_0201f2b8 {
    char pad_00[0x100];
    UnkStruct_0201f2b8_3 *inner;
    unsigned char buf[0x20];
} UnkStruct_0201f2b8;

typedef struct UnkStruct_0201f2b8_2 {
    void *ptr;
    unsigned char byte;
} UnkStruct_0201f2b8_2;

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(UnkStruct_0201f2b8 *, unsigned char *, unsigned char *, int, int, int, int, int, int);

extern struct {
    int word;
    unsigned char byte;
} data_020c8ba0;

void func_0201f2b8(UnkStruct_0201f2b8 *s, UnkStruct_0201f2b8_2 *out)
{
    func_0202da38(s, s->buf, &s->buf[0x1e], 30, func_020036e8(func_0208150c(s->inner->unk_830)), data_020c8ba0.word, 1, 7,
                  data_020c8ba0.byte);
    out->ptr = s->buf;
    out->byte = s->buf[0x1e];
}
