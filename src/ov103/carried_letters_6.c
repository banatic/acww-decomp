/* carried_letters_6: 6 functions, module ov103
 * mwccarm 1.2/base -O4,s
 * func_ov103_0229ce0c @ 0x0229ce0c, 0xc bytes, Thumb
 * func_ov103_0229cdfc @ 0x0229cdfc, 0x10 bytes, Thumb
 * func_ov103_0229cde8 @ 0x0229cde8, 0x14 bytes, Thumb
 * func_ov103_0229cdd8 @ 0x0229cdd8, 0x10 bytes, Thumb
 * func_ov103_0229cd98 @ 0x0229cd98, 0x40 bytes, Thumb
 * func_ov103_0229cd4c @ 0x0229cd4c, 0x4c bytes, Thumb
 */

extern void func_020b9ccc(void *p);
extern int func_ov094_0229bba4(char *p, int arg1, int arg2);
extern int func_ov094_0229b30c(char *p, int v);
extern int func_ov103_0229cc08(void *arg0, void *arg1);
extern int func_ov103_0229cce8(int a, int b);
extern int func_02066830(int a, int b);
extern void func_ov103_0229cd1c(int a, int b, int c);
extern void func_ov103_0229c8e8(int a, int b);

void func_ov103_0229ce0c(void *p)
{
    func_020b9ccc((char *) p + 0x94);
}

int func_ov103_0229cdfc(int a, unsigned int b)
{
    if (b >= 0xb && b <= 0x14) {
        return 1;
    } else {
        return 0;
    }
}

unsigned char func_ov103_0229cde8(unsigned char param1, unsigned char param2)
{
    if (param2 >= 0xb && param2 <= 0x14) {
        return param2 - 0xb;
    }
    return 0;
}

unsigned char func_ov103_0229cdd8(int a, unsigned int b)
{
    if (b <= 9) {
        return (unsigned char) (b + 11);
    } else {
        return 21;
    }
}

int func_ov103_0229cd98(char *base, int a1, int a2, int flag)
{
    int res1;

    res1 = func_ov094_0229bba4(base + 0xb2c, a1, a2);
    if (res1 != 0x37) {
        if (flag != 0) {
            if (func_ov094_0229b30c(base + 0xb2c, res1) != 0) {
                return 0x15;
            }
        }
        return (int) func_ov103_0229cdd8((int) base, res1);
    } else {
        return 0x15;
    }
}

int func_ov103_0229cd4c(int a, int b)
{
    int r5 = a;
    int r4 = b;
    if (func_ov103_0229cc08((void *) a, (void *) b) == 0) {
        int r1 = func_ov103_0229cce8(r5, r4);
        func_02066830(r5 + 0x2ca0, r1);
        func_ov103_0229cd1c(r5, *(unsigned char *) (r5 + 0x2da3), r5 + 0x2ca0);
    }
    func_ov103_0229c8e8(r5, r4);
    return 1;
}
