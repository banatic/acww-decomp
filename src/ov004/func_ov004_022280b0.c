/* func_ov004_022280b0 @ 0x022280b0, 0x50 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022280b0 {
    int a;
    unsigned char b;
    int c;
    int d;
};
extern void func_02057d58(void *dst, int a, int b, int c, void *self, int d);
extern void func_020109a0(void *self, int a, int b, int c);
extern void func_02057d0c(int k, void *self);
extern int func_020b65c4(void);
extern void func_0200f328(void *self, int msg);
void func_ov004_022280b0(unsigned char *self, unsigned char *p)
{
    struct UnkStruct_022280b0 *q;
    q = (struct UnkStruct_022280b0 *) (p + 0xc);
    func_02057d58(self + 0x820, *(int *) (p + 0xc), q->b, q->c, self, q->d);
    func_020109a0(self, 0x2e, 3, 0);
    func_02057d0c(1, self);
    if (func_020b65c4() == 9) {
        func_0200f328(self, 0x4f);
    }
}
