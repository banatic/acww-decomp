/* func_ov121_0229a3a8 @ 0x0229a3a8, 0x54 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov121_0229af58(char *self, unsigned char b);
extern int func_ov121_02299a5c(char *self, int n);
extern int func_ov121_02299fc8(char *self);

int func_ov121_0229a3a8(char *self)
{
    int result = func_ov121_0229af58(self, *(unsigned char *) (self + 0xb1));
    if (func_ov121_02299a5c(self, 0x40)) {
        result += 0x100;
    } else if (func_ov121_02299a5c(self, 0x20)) {
        result -= 0x100;
    }
    if (func_ov121_02299fc8(self) == -1) {
        result += 0xb;
    }
    return result;
}
