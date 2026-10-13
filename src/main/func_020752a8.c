/* func_020752a8 @ 0x020752a8, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_020752a8 {
    char pad_00[0x68];
    void *unk_68;
} UnkStruct_020752a8;

extern UnkStruct_020752a8 *data_020ccf94;
extern int func_020b65c4(void *);
extern int func_020a132c(void);
extern void *func_020a245c(int);
extern void *func_020962a4(void *, void *);
extern char *func_020984e8(void *);
extern void MI_CpuCopy8(const void *, void *, unsigned int);

void func_020752a8(char *p, int n)
{
    int off;
    UnkStruct_020752a8 *g;
    void *t;
    char *dst;

    if (func_020b65c4(p) != 0x2e) {
        return;
    }
    if (func_020a132c() == 0) {
        return;
    }
    MI_CpuCopy8(p, &off, 4);
    t = func_020a245c(func_020a132c());
    g = data_020ccf94;
    g->unk_68 = 0;
    dst = func_020984e8(func_020962a4(g->unk_68, t));
    MI_CpuCopy8(p + 4, dst + off, n - 4);
}
