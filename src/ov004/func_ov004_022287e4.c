/* func_ov004_022287e4 @ 0x022287e4, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O1,s
 */

struct UnkStruct_022287e4 {
    int a;
    int b;
    int c;
};
extern void func_020109a0(void *self, int a, int b, unsigned short d);
extern void func_0200fa1c(struct UnkStruct_022287e4 *out, void *self, struct UnkStruct_022287e4 *in, unsigned short *p,
                          int *q);
extern void *func_ov004_02228840(void *dst, struct UnkStruct_022287e4 *out);
extern void func_ov004_0223a6ac(void *p);
extern int data_ov004_02247780;
extern unsigned char data_020e54a8;
void func_ov004_022287e4(unsigned char *self, void *message, int previous)
{
    struct UnkStruct_022287e4 out;
    int t;
    func_020109a0(self, 0x27, 0, 0);
    func_0200fa1c(&out, self, (struct UnkStruct_022287e4 *) (self + 0x5c), (unsigned short *) (self + 0x8e),
                  &data_ov004_02247780);
    func_ov004_02228840(self + 0x7d4, &out);
    t = (data_020e54a8 == 1) ? 1 : 0;
    if (t != 0) {
        func_ov004_0223a6ac(self + 0x5c);
    }
}
