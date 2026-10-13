/* func_02054860 @ 0x02054860, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02054cdc(void *p);
extern int func_02056e84(void *p);
extern void func_02054700(void *p);
extern void func_02056ffc(void *p);

typedef struct {
    char pad_00[0x04];
    unsigned short flags;        // 0x04
    char pad_06[0xf4 - 0x06];    // to 0xf4
    unsigned int *unk_F4;        // 0xf4
    char unk_F8;                 // 0xf8
    char pad_F9[0x100 - 0xf9];   // to 0x100
    unsigned int unk_100;        // 0x100
    char pad_104[0x110 - 0x104]; // to 0x110
    char unk_110;                // 0x110
    char pad_111[0x14c - 0x111]; // to 0x14c
    unsigned int unk_14C;        // 0x14c
    unsigned int unk_150;        // 0x150
} UnkStruct_02054860;

void func_02054860(UnkStruct_02054860 *p)
{
    func_02054cdc(p);
    if (p->unk_14C != 0 || p->unk_150 != 0) {
        if (func_02056e84(&p->unk_110) != 0 && (p->flags & 0x4000) != 0) {
            func_02054700(p);
            p->flags &= ~0x4000;
        }
        func_02056ffc(&p->unk_F8);
        *p->unk_F4 = p->unk_100;
    }
}
