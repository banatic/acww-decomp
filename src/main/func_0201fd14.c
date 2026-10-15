/* func_0201fd14 @ 0x0201fd14, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int arg);
extern int func_020036e8(int arg);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

typedef struct {
    unsigned char pad_00[0x100];
    int *unk_100;
    unsigned char sub_0x104[0x1e];
    unsigned char unk_122;
} InputStruct;

typedef struct {
    int unk_00;
    unsigned char unk_04;
} UnkStruct_0201fd14;

typedef struct {
    void *unk_00;
    unsigned char unk_04;
} OutputStruct;

extern UnkStruct_0201fd14 data_020c8ce8;

void func_0201fd14(InputStruct *p, OutputStruct *out)
{
    int v = func_020036e8(func_0208150c(*(int *) ((char *) p->unk_100 + 0x830)));
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 0x1e, v, data_020c8ce8.unk_00, 1, 0xa, data_020c8ce8.unk_04);
    out->unk_00 = (char *) p + 0x104;
    out->unk_04 = p->unk_122;
}
