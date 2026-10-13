/* func_0201516c @ 0x0201516c, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02019d0c(unsigned int, int, int, int, int, int, int, int, int, unsigned short, int);
extern void func_02068440(unsigned int);
extern unsigned short data_020c80f8;

typedef struct {
    unsigned char pad_00[0x40];
    unsigned int unk_40;
    unsigned char pad_44[8];
    unsigned int unk_4C;
    unsigned char pad_50[0x5c];
    unsigned char unk_AC;
} UnkStruct_0201516c;

int func_0201516c(UnkStruct_0201516c *p)
{
    if (p->unk_4C != 0 && p->unk_40 != 0) {
        if (func_02019d0c(p->unk_4C + 0x564, 0xf, 4, 0, 0, 0, 0, 0, 0, data_020c80f8, 0)) {
            func_02068440(p->unk_40);
            p->unk_AC = 1;
        }
    }
    return 0;
}
