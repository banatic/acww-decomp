/* func_ov073_022796c8 @ 0x022796c8, 0x28 bytes, Thumb, module ov073
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *p);
extern int func_0208602c(int a);
extern int func_020860b8(int a);
extern void func_02087864(int a, int b, int c);

struct S_022796c8 {
    unsigned char pad_00[0x5c];
    unsigned int unk_5C;
    unsigned char pad_60[0x4];
    unsigned int unk_64;
};

int func_ov073_022796c8(struct S_022796c8 *p)
{
    int v;

    v = func_0202ec14(p);
    if (v == 0) {
        return 0;
    }
    func_02087864(func_020860b8(func_0208602c(v)), p->unk_5C, p->unk_64);
    return 1;
}
