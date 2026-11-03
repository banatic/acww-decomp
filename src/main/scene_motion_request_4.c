/* scene_motion_request_4: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02019c90 @ 0x02019c90, 0x38 bytes, Thumb
 * func_02019c6c @ 0x02019c6c, 0x24 bytes, Thumb
 */

struct Func02019c90Struct {
    unsigned char pad_00[0x4d];
    unsigned char flag;
};

extern int func_02019d0c(struct Func02019c90Struct *, int, int, int, int, int, int, int, int, int, int);

int func_02019c90(struct Func02019c90Struct *p1, int p2, int p3, int p4)
{
    int ret = 0;
    if (func_02019d0c(p1, 8, p2, 0, 0, 0, 0, 0, 0, p4, 0)) {
        p1->flag = (unsigned char) p3;
        ret = 1;
    }
    return ret;
}

int func_02019c6c(int a, int b, int c)
{
    return func_02019d0c((struct Func02019c90Struct *) a, 0, b, 0, 0, 0, 0, 0, 0, c, 0);
}
