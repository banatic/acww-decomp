/* func_ov084_02279120 @ 0x02279120, 0x94 bytes, Thumb, module ov084
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[8];
} UnkStruct_02279120;

extern int func_0202ec58(void *p);
extern void func_ov084_02279080(void *p, int a);
extern void func_020866b8(void *p, int a);
extern void func_02016764(void *a, void *b, int c, int d, int e, int f, int g, int h);
extern void func_02054188(void *a, int b, int c);
extern void func_0209df64(void *p);
extern int _s32_div_f(int a, int b);

extern unsigned char data_021f3aa4[];

int func_ov084_02279120(unsigned char *self)
{
    if (func_0202ec58(self) == 0) {
        return 0;
    }

    func_ov084_02279080(self, 0);
    func_020866b8((void *) data_021f3aa4, 0);
    func_02016764(self + 0x334, self, 0x140, 0, 0, 0x1000, 0, 1);
    func_02054188(self + 0xec, 12, 14);

    *(unsigned int *) (self + 0x4e8) |= 2;

    {
        UnkStruct_02279120 local;
        func_0209df64(&local);
        *(unsigned char *) (self + 0x714) = (unsigned char) _s32_div_f(((unsigned char *) &local)[0] - 1, 7);
        ++*(unsigned char *) (self + 0x714);
    }

    return 1;
}
