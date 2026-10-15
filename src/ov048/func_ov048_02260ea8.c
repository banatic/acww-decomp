/* func_ov048_02260ea8 @ 0x02260ea8, 0x58 bytes, Thumb, module ov048
 * mwccarm 1.2/base -O4,s
 */

extern int func_020e8840(int);
extern int func_020eba18(void);
extern int func_020eba08(void);
extern int func_ov048_0226077c(void *, int);
extern void func_ov048_02260e28(void *receiver, int code, int flag);

int func_ov048_02260ea8(void *self)
{
    if (func_020e8840(*(unsigned int *) ((char *) self + 0xb8) + 0xe6e) == 0) {
        func_ov048_02260e28(self, 0x7a, 1);
        return 1;
    } else {
        if (func_020eba18() != 0) {
            int v = func_020eba08();
            if (v < 0) {
                v = -v;
            }
            v = func_ov048_0226077c(self, v);
            func_ov048_02260e28(self, v, 1);
            return 1;
        } else {
            return 0;
        }
    }
}
