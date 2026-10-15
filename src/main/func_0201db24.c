/* func_0201db24 @ 0x0201db24, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0201db24 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0201db24_2 {
    char pad_00[0x100];
    struct UnkStruct_0201db24 *unk_100;
    unsigned char unk_104[30];
    unsigned char unk_122;
};

struct UnkStruct_0201db24_3 {
    unsigned char *field0;
    unsigned char unk_04;
};

extern struct {
    unsigned int field0;
    unsigned char field4;
} data_020c8d18;

extern int func_0208150c(unsigned int);
extern int func_020036e8(int);
extern int func_0202da38(struct UnkStruct_0201db24_2 *, unsigned char *, unsigned char *, int, int, int, int, int, int);

unsigned char func_0201db24(struct UnkStruct_0201db24_2 *s, struct UnkStruct_0201db24_3 *out)
{
    unsigned char c;
    func_0202da38(s, s->unk_104, &s->unk_122, 0x1e, func_020036e8(func_0208150c(s->unk_100->unk_830)), data_020c8d18.field0, 1,
                  4, data_020c8d18.field4);
    out->field0 = s->unk_104;
    c = s->unk_122;
    out->unk_04 = c;
    return c;
}
