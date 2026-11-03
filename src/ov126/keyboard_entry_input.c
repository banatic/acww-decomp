/* keyboard_entry_input: 5 functions, module ov126
 * mwccarm 1.2/base -O4,s
 * func_ov126_0229fe28 @ 0x0229fe28, 0x78 bytes, Thumb
 * func_ov126_0229fdd4 @ 0x0229fdd4, 0x54 bytes, Thumb
 * func_ov126_0229fd64 @ 0x0229fd64, 0x70 bytes, Thumb
 * func_ov126_0229fcfc @ 0x0229fcfc, 0x68 bytes, Thumb
 * func_ov126_0229fcd8 @ 0x0229fcd8, 0x24 bytes, Thumb
 */

extern int func_ov095_02299a00(char *p);
extern int func_ov002_0220a620(char *p, int a);
extern int func_ov095_0229c448(char *p, int a, int b);
extern void func_ov095_0229c8e4(char *p, int a);
extern void func_ov126_0229feec(void *p);
extern int func_ov126_022a027c(void *param, int n);
extern void func_ov095_0229bf3c(void *param);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern int func_ov126_022a0a50(void *param);
extern unsigned short data_021fbe40[];
extern int func_ov095_0229cf64(void *ptr, int val);
extern int func_ov126_022a03dc(void *ptr, int val);
extern void func_ov126_0229ff0c(void *ptr);
extern int func_ov126_022a0a90(int);

int func_ov126_0229fe28(void *arg)
{
    int r4;
    if (!((*(struct { char pad[2]; unsigned short flag; } *) data_021fbe40).flag & 1)) {
        return 0;
    }
    r4 = func_ov095_02299a00((char *) arg + 0x19c);
    if (r4 == -1) {
        return 0;
    }
    if (func_ov002_0220a620((char *) arg + 0x3dc4, 6) != 0 && r4 == 263) {
        return 0;
    }
    func_ov095_0229c448((char *) arg + 0x19c, r4, 9);
    func_ov095_0229c8e4((char *) arg + 0x19c, r4);
    func_ov126_0229feec(arg);
    return 1;
}

int func_ov126_0229fdd4(void *param)
{
    if (((*(unsigned short *) data_021fbe40) & 2) == 0) {
        return 0;
    }

    if (func_ov126_022a027c(param, 0) != 0) {
        func_ov095_0229bf3c((char *) param + 0x19c);
        ((unsigned char *) param)[0xae] = ((unsigned char *) param)[0x8d];
        func_ov002_02208098((void *) (param), 0xc);
    } else {
        func_ov126_022a0a50(param);
    }
    return 1;
}

int func_ov126_0229fd64(void *param)
{
    if (!(data_021fbe40[1] & 0x100)) {
        return 0;
    }

    if (func_ov095_0229cf64((char *) param + 0x19c, 0xc)) {
        return 0;
    }

    func_ov126_022a03dc(param, 0x119);
    func_ov095_0229c8e4((char *) ((char *) param + 0x19c), 0x10a);
    func_ov126_0229ff0c(param);

    *((unsigned char *) param + 0xae) = *((unsigned char *) param + 0x8d);

    func_ov002_02208098((void *) (param), 0xe);
    return 0;
}

int func_ov126_0229fcfc(char *self)
{
    if (!(((unsigned short *) ((unsigned char *) data_021fbe40))[1] & 0x200)) {
        return 0;
    }
    if (func_ov095_0229cf64((void *) (self + 0x19c), 11)) {
        return 0;
    }
    func_ov126_022a03dc((void *) self, 0x118);
    func_ov095_0229c8e4(self + 0x19c, 0x109);
    *(unsigned char *) (self + 0xae) = *(unsigned char *) (self + 0x8d);
    func_ov002_02208098((void *) (self), 13);
    return 0;
}

int func_ov126_0229fcd8(int arg)
{
    if (!(data_021fbe40[1] & 8)) {
        return 0;
    }
    func_ov126_022a0a90(arg);
    return 1;
}
