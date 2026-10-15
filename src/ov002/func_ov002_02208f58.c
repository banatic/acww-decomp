/* func_ov002_02208f58 @ 0x02208f58, 0x52 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02208ff8(void *a, int i);
extern int func_ov002_02208fac(void *a, int i);
extern void func_ov002_022089ec(void *self, void *a, int code);

void func_ov002_02208f58(void *self, void *a, unsigned int k)
{
    if (k >= 1 && k < 5) {
        func_ov002_02208ff8(a, k - 1);
    } else if (k >= 5 && k < 0xd) {
        func_ov002_02208fac(a, k - 5);
    } else {
        switch (k) {
            case 0xd:
                func_ov002_022089ec(self, a, 0x25);
                break;
            case 0xe:
                func_ov002_022089ec(self, a, 0x1e);
                break;
            case 0xf:
                func_ov002_022089ec(self, a, 0x27);
                break;
        }
    }
}
