/* func_020b5724 @ 0x020b5724, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x5c];
    unsigned char unk_5C;
    unsigned char unk_5D;
    unsigned char unk_5E;
    unsigned char pad_5F;
    unsigned char pad_60[4];
    unsigned int unk_64;
    unsigned int unk_68;
} UnkStruct_020b5724;

extern int func_020a16e0(void);
extern void MI_CpuCopy8(unsigned int, unsigned int, unsigned int);

extern unsigned char data_021dc7a8[];

void func_020b5724(UnkStruct_020b5724 *p)
{
    unsigned char a = p->unk_5C;

    if (a == 1 || p->unk_5D == 1) {
        p->unk_5E = 1;
        return;
    }

    if (a != 0 && p->unk_5D != 0) {
        p->unk_5E = 4;
        return;
    }

    {
        int cond;

        if (a != 0) {
            cond = 1;
        } else if (p->unk_5D != 0) {
            cond = 0;
        } else {
            cond = func_020a16e0();
        }

        if (cond == 0) {
            MI_CpuCopy8(p->unk_64, (unsigned int) data_021dc7a8, 0x173fc);
        } else {
            MI_CpuCopy8(p->unk_68, (unsigned int) data_021dc7a8, 0x173fc);
        }

        p->unk_5E = 0;
    }
}