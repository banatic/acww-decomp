/* func_ov126_022a1108 @ 0x022a1108, 0x74 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char unk_00[0x3dc8];
} Context;

extern int func_ov002_02208054(void *p, int a);
extern int func_ov002_0220a784(void *p, int a);
extern int func_ov002_0220a720(void *p, int a);
extern int func_ov002_02208098(void *p, int a);
extern void func_ov126_022a0bb0(void *p);

void func_ov126_022a1108(Context *p)
{
    if (func_ov002_02208054(p, 1) != 0) {
        func_ov126_022a0bb0(p);
        return;
    }
    if (func_ov002_0220a784(&p->unk_00[0x3dc4], 3) != 0) {
        func_ov002_0220a720(&p->unk_00[0x3dc4], 3);
        p->unk_00[0x8c] = 3;
        func_ov002_02208098(p, 0xf);
        return;
    }
    if (func_ov002_0220a784(&p->unk_00[0x3dc4], 4) != 0) {
        func_ov002_0220a720(&p->unk_00[0x3dc4], 4);
        p->unk_00[0x8c] = 9;
        func_ov002_02208098(p, 0xf);
    }
}
