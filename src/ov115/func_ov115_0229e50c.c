/* func_ov115_0229e50c @ 0x0229e50c, 0x98 bytes, Thumb, module ov115
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206f58c(void);
extern int func_0206f56c(void);
extern int func_0206fe60(void);
extern int func_ov090_022990e0(void);
extern int func_ov115_0229e4cc(void *p, int n);

typedef struct {
    char pad[0x8d];
    unsigned char flag;
} UnkStruct_0229e50c;

extern struct {
    char pad[2];
    unsigned short field;
} data_021fbe40;

int func_ov115_0229e50c(UnkStruct_0229e50c *p)
{
    volatile int unused;
    int ret;

    func_0206f58c();
    if (func_0206f56c() != 0) {
        return func_ov115_0229e4cc(p, 7);
    }
    if (p->flag != 0 && p->flag != 2) {
        return 0;
    }

    ret = -1;
    if (func_0206fe60() != 0) {
        ret = func_ov090_022990e0();
    } else {
        unsigned short v = data_021fbe40.field;
        if ((v & 2) != 0) {
            ret = 7;
        } else if ((v & 0x800) != 0) {
            ret = 0;
        } else if ((v & 0x400) != 0) {
            ret = 5;
        } else if ((v & 4) != 0) {
            ret = 4;
        }
    }

    return func_ov115_0229e4cc(p, ret);
}
