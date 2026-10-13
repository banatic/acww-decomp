/* func_0209fafc @ 0x0209fafc, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);

struct UnkStruct_0209fafc {
    char pad_00[3];
    unsigned char b;
};

void func_0209fafc(struct UnkStruct_0209fafc *p)
{
    unsigned char orig = p->b;
    p->b = func_020644cc(0xff);
    if (p->b == orig) {
        if (p->b < 0xff) {
            p->b++;
        } else {
            p->b--;
        }
    }
}
