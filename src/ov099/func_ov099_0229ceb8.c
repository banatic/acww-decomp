/* func_ov099_0229ceb8 @ 0x0229ceb8, 0x3a bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xcc];
    int unk_CC;
} UnkStruct_0229ceb8;

extern int func_ov094_0229aee8(void *ptr, int arg1, int arg2);
extern int func_ov094_0229a69c(void *ptr, int v);
extern int func_ov099_0229cef4(UnkStruct_0229ceb8 *p, int v);

int func_ov099_0229ceb8(UnkStruct_0229ceb8 *p1, int a, int b, int c)
{
    int v;
    v = func_ov094_0229aee8(&p1->unk_CC, a, b);
    if (v == 0x23) {
        goto ret1;
    }
    if (c != 0 && func_ov094_0229a69c(&p1->unk_CC, v) != 0) {
        return 0x1d;
    }
    return func_ov099_0229cef4(p1, v);
ret1:
    return 0x1d;
}
