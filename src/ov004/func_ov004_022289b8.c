/* func_ov004_022289b8 @ 0x022289b8, 0x74 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022289b8 {
    int a;
    int b;
    int c;
};
extern void func_0200fa1c(struct UnkStruct_022289b8 *out, void *self, struct UnkStruct_022289b8 *in, unsigned short *p,
                          int *q);
extern void *func_ov004_02228a2c(void *dst, struct UnkStruct_022289b8 *v, int b);
extern int func_02073908(int a, int b);
extern void func_02051ea4(struct UnkStruct_022289b8 *out);
extern short data_ov004_0224776c[];
extern int data_ov004_02247780;
extern int data_020ccf94;
void func_ov004_022289b8(unsigned char *self, unsigned char *p, int previous)
{
    short sh;
    struct UnkStruct_022289b8 out, v;
    int b;

    b = *(unsigned char *) (p + 0xc);
    sh = (short) (*(short *) (self + 0x8e) - data_ov004_0224776c[b]);
    func_0200fa1c(&out, self, (struct UnkStruct_022289b8 *) (self + 0x5c), (unsigned short *) &sh, &data_ov004_02247780);
    v.a = out.a;
    v.b = out.b;
    v.c = out.c;
    func_ov004_02228a2c(self + 0x7d4, &v, b);
    if (func_02073908(data_020ccf94, *(int *) (self + 0x800)) != 0) {
        func_02051ea4(&out);
    }
}
