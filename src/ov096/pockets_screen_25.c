/* pockets_screen_25: 3 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_0229ed74 @ 0x0229ed74, 0x78 bytes, Thumb
 * func_ov096_0229ed44 @ 0x0229ed44, 0x30 bytes, Thumb
 * func_ov096_0229ec90 @ 0x0229ec90, 0xb4 bytes, Thumb
 */

extern int func_ov096_0229f830(char *obj, int arg);
extern int func_ov096_0229f7ac(char *obj, int arg);
extern int func_ov096_0229f820(char *obj, int arg);
extern int func_ov096_0229f548(char *obj, int arg);
extern void func_ov094_0229b98c(char *p);
extern void func_ov094_0229ab1c(char *p, int arg);
extern void func_ov094_0229ab5c(char *p);
extern void func_ov094_0229b950(char *p, int arg);
extern void func_ov094_0229ab0c(void *);
extern void func_ov094_0229b944(void *);
extern void func_ov094_02299ac4(void *);
extern int func_ov096_0229f800(void *self, unsigned int cmd);
extern void func_ov094_0229aafc(void *obj, int val);
extern void func_ov094_0229b938(void *obj, int val);
extern void func_ov094_02299acc(void *obj, int val);

void func_ov096_0229ed74(char *obj, int arg)
{
    if (func_ov096_0229f830(obj, arg)) {
        int res = func_ov096_0229f7ac(obj, arg);
        func_ov094_0229b98c(obj + 0xdb8);
        func_ov094_0229ab1c(obj + 0x358, res);
    } else {
        if (func_ov096_0229f820(obj, arg)) {
            int res = func_ov096_0229f548(obj, arg);
            func_ov094_0229ab5c(obj + 0x358);
            func_ov094_0229b950(obj + 0xdb8, res);
        } else {
            func_ov094_0229ab5c(obj + 0x358);
            func_ov094_0229b98c(obj + 0xdb8);
        }
    }
}

void func_ov096_0229ed44(void *self)
{
    func_ov094_0229ab0c((char *) self + 0x358);
    func_ov094_0229b944((char *) self + 0xdb8);
    func_ov094_02299ac4((char *) self + 0xde0);
}

void func_ov096_0229ec90(void *self, unsigned int cmd)
{
    if (func_ov096_0229f830((char *) self, cmd)) {
        func_ov094_0229aafc((char *) self + 0x358, func_ov096_0229f7ac((char *) self, cmd));
    } else if (func_ov096_0229f820((char *) self, cmd)) {
        func_ov094_0229b938((char *) self + 0xdb8, func_ov096_0229f548((char *) self, cmd));
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
