/* func_020396fc @ 0x020396fc, 0x52 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020396dc(int, int);
extern int func_02039628(void *a, void *b);
extern int func_020396d0(void *a, int b);
extern void func_02039f0c(void *a, int b, int c, int d);
extern void func_020392a0(int a, void *b);

typedef struct UnkStruct_020396fc {
    char pad_00[0xC];
    int unk_0C;
    char pad_10[0xA8];
} UnkStruct_020396fc;

void func_020396fc(void *arg0, int arg1, int arg2, int arg3)
{
    int idx;
    UnkStruct_020396fc *r6;
    int ret;

    if (arg1 > 4) {
        return;
    }
    idx = func_020396dc((int) arg0, arg1);
    r6 = (UnkStruct_020396fc *) ((char *) arg0 + 4 + idx * 184);
    if (func_02039628(arg0, r6) == 0) {
        return;
    }
    ret = func_020396d0(arg0, arg1);
    func_02039f0c(r6, arg2, arg3, ret);
    if (r6->unk_0C != 0) {
        return;
    }
    func_020392a0(arg1, r6);
}
