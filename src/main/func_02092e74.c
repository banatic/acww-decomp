/* func_02092e74 @ 0x02092e74, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct InnerStruct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
    char pad_54[0x68 - 0x54];
    char unk_68;
};

struct OuterStruct {
    char pad_00[0xc];
    struct InnerStruct *inner;
};

extern void func_02094c38(struct OuterStruct *s, int, const void *);
extern const unsigned char data_020d1750[];

void func_02092e74(struct OuterStruct *s, char c, int a, int b)
{
    func_02094c38(s, 0, data_020d1750);
    s->inner->unk_68 = c;
    s->inner->unk_4C = a;
    s->inner->unk_50 = b;
}
