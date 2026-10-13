/* func_ov099_0229cc74 @ 0x0229cc74, 0x54 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov099_0229cf30(char *self, int param);
extern int func_ov099_0229cf04(char *self, int param);
extern int func_ov099_0229cf20(char *self, int param);
extern int func_ov099_0229ce14(char *self, int param);
extern int func_ov094_0229a69c(char *addr, int value);
extern int func_ov094_0229b30c(char *addr, int value);

int func_ov099_0229cc74(char *self, int param)
{
    if (func_ov099_0229cf30(self, param)) {
        int v;
        v = func_ov099_0229cf04(self, param);
        self += 0xcc;
        return func_ov094_0229a69c(self, v);
    } else {
        if (func_ov099_0229cf20(self, param)) {
            int v2;
            v2 = func_ov099_0229ce14(self, param);
            return func_ov094_0229b30c(self + 0xb2c, v2);
        } else {
            return 1;
        }
    }
}
