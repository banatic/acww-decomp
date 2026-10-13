/* func_ov109_0229cc4c @ 0x0229cc4c, 0x3a bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xcc];
    int unk_CC;
} UnkStruct_0229cc4c;

extern int func_ov094_0229aee8(void *ptr);
extern int func_ov119_0229a69c(void *ptr, int v);
extern int func_ov109_0229cc88(UnkStruct_0229cc4c *p, int v);

int func_ov109_0229cc4c(UnkStruct_0229cc4c *p1, int a, int b, int c)
{
    int v;
    v = func_ov094_0229aee8(&p1->unk_CC);
    if (v == 0x23) {
        goto ret1;
    }
    if (c != 0 && func_ov119_0229a69c(&p1->unk_CC, v) != 0) {
        return 0x10;
    }
    return func_ov109_0229cc88(p1, v);
ret1:
    return 0x10;
}
