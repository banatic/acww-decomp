/* func_ov109_0229c85c @ 0x0229c85c, 0x48 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov109_0229cbd4(void *self, unsigned char c);
extern int func_ov109_0229c2ac(void *self, int n);

int func_ov109_0229c85c(void *self)
{
    int result = func_ov109_0229cbd4(self, *((unsigned char *) self + 0x29d3));
    if (func_ov109_0229c2ac(self, 16) != 0) {
        result += 0x100;
    } else if (func_ov109_0229c2ac(self, 8) != 0) {
        result -= 0x100;
    }
    result += 8;
    return result;
}
