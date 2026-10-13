/* func_ov004_02229010 @ 0x02229010, 0x68 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02229010 {
    int a;
    int b;
    int c;
};
struct UnkStruct_02229010_2 {
    int a;
    int b;
    int c;
};
struct UnkStruct_02229010_3 {
    int a;
    int b;
    int c;
    int d;
};
extern void func_0200e92c(struct UnkStruct_02229010_2 *c);
extern void func_0200e90c(struct UnkStruct_02229010_2 *c, int k, int a, int b);
extern void func_0200fa1c(struct UnkStruct_02229010 *out, void *self, struct UnkStruct_02229010 *in, unsigned short *p,
                          int *q);
extern void func_ov004_02229078(struct UnkStruct_02229010_3 *o, int a, int c, short ang);
extern int func_0200e894(void *self, struct UnkStruct_02229010_2 *c);
extern void func_0200e91c(struct UnkStruct_02229010_2 *c);
extern int data_ov004_02247780;
int func_ov004_02229010(unsigned char *self, int a, int b)
{
    struct UnkStruct_02229010_2 ctx;
    struct UnkStruct_02229010_3 obj;
    struct UnkStruct_02229010 out;
    short ang;
    int r;

    func_0200e92c(&ctx);
    func_0200e90c(&ctx, 0x27, a, b);
    func_0200fa1c(&out, self, (struct UnkStruct_02229010 *) (self + 0x5c), (unsigned short *) (self + 0x8e),
                  &data_ov004_02247780);
    ang = (short) (*(short *) (self + 0x8e) - 0x4000);
    func_ov004_02229078(&obj, out.a, out.c, ang);
    r = func_0200e894(self, &ctx);
    func_0200e91c(&ctx);
    return r;
}
