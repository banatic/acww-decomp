/* func_ov109_0229c2c4 @ 0x0229c2c4, 0x6c bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229c28c(void *p, int x);
extern int func_ov109_0229ccb4(void *p, unsigned char b);
extern void func_ov109_0229c330(void *p, int a);
extern int func_ov002_022088cc(int a);
extern void func_ov002_0220a2b4(void *p);

int func_ov109_0229c2c4(unsigned char *p, int a)
{
    unsigned char old = *(p + 0x29d3);
    func_ov109_0229c28c(p, 0x18);
    if (a == 0) {
        return 0;
    }

    if (func_ov109_0229ccb4(p, *(p + 0x29d3))) {
        func_ov109_0229c330(p, a);
    } else {
        if (*(p + 0x29d3) == 0xf) {
            if (func_ov002_022088cc(a)) {
                *(p + 0x29d3) = 0xe;
                func_ov002_0220a2b4(p + 0x2274);
            }
        }
    }

    if (old == *(p + 0x29d3)) {
        return 0;
    } else {
        return 1;
    }
}
