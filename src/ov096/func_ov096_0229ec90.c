/* func_ov096_0229ec90 @ 0x0229ec90, 0xb4 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f830(void *self, unsigned int cmd);
extern int func_ov096_0229f7ac(void *self, unsigned int cmd);
extern int func_ov096_0229f820(void *self, unsigned int cmd);
extern int func_ov096_0229f548(void *self, unsigned int cmd);
extern int func_ov096_0229f800(void *self, unsigned int cmd);

extern void func_ov094_0229aafc(void *obj, int val);
extern void func_ov094_0229b938(void *obj, int val);
extern void func_ov094_02299acc(void *obj, int val);

void func_ov096_0229ec90(void *self, unsigned int cmd)
{
    if (func_ov096_0229f830(self, cmd)) {
        func_ov094_0229aafc((char *) self + 0x358, func_ov096_0229f7ac(self, cmd));
    } else if (func_ov096_0229f820(self, cmd)) {
        func_ov094_0229b938((char *) self + 0xdb8, func_ov096_0229f548(self, cmd));
    } else if (func_ov096_0229f800(self, cmd)) {
        switch (cmd - 0x22) {
            case 3:
                func_ov094_0229aafc((char *) self + 0x358, 0x21);
                break;
            case 0:
            case 1:
                func_ov094_02299acc((char *) self + 0xde0, 0);
                break;
            case 2:
                func_ov094_02299acc((char *) self + 0xde0, 1);
                break;
        }
    } else {
        if (cmd == 0x21) {
            func_ov094_0229aafc((char *) self + 0x358, 0x22);
        }
    }
}
