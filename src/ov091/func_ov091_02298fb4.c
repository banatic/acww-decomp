/* func_ov091_02298fb4 @ 0x02298fb4, 0x50 bytes, Thumb, module ov091
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208014(void *receiver);
extern void func_ov091_02298fa8(void *p);
extern void func_ov002_0220a1dc(void *p);
extern unsigned char *func_ov002_022080a0(void *p, unsigned char value);

typedef struct UnkStruct_02298fb4 {
    unsigned char pad_00[0x8c];
    unsigned char unk_8C;
    unsigned char pad_8D[0x434 - 0x8c - 1];
    char sub[1];
} UnkStruct_02298fb4;

typedef struct Global {
    unsigned char pad_00[2];
    unsigned short flags;
} Global;

extern Global data_021fbe40;

void func_ov091_02298fb4(UnkStruct_02298fb4 *p)
{
    if (func_ov002_02208014(p)) {
        func_ov091_02298fa8(p);
        return;
    }
    {
        unsigned short f = data_021fbe40.flags;
        if ((f & 1) || (f & 2)) {
            func_ov002_0220a1dc(&p->sub);
            p->unk_8C = 2;
            func_ov002_022080a0(p, 1);
        }
    }
}
