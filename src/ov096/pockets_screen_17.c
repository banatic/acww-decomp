/* pockets_screen_17: 4 functions, module ov096
 * mwccarm 1.2/base -O4,s
 * func_ov096_022a011c @ 0x022a011c, 0x34 bytes, Thumb
 * func_ov096_022a00b4 @ 0x022a00b4, 0x68 bytes, Thumb
 * func_ov096_022a0094 @ 0x022a0094, 0x20 bytes, Thumb
 * func_ov096_022a0074 @ 0x022a0074, 0x20 bytes, Thumb
 */

extern int func_ov002_0220b8ac(void *ptr, int val);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_0208e5cc(void *ptr);
extern int func_0208e4bc(char *);
extern int func_ov002_0220b57c(char *);
extern int func_ov002_0220b5ec(char *, int);
extern int func_ov002_0220b59c(char *, int);
extern void func_ov002_0220a0b4(char *, int, int);
extern void func_ov002_02208090(char *, int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov096_0229ddd8(char *);
extern int func_ov002_02208e28(void *ptr);
extern void func_ov096_0229fb4c(void *ptr);
extern int func_ov096_022a018c(int argument0);

void func_ov096_022a011c(void *arg0)
{
    if (func_ov002_0220b8ac((char *) arg0 + 0x2958, 1)) {
        func_ov002_02208098((void *) (arg0), *((unsigned char *) arg0 + 0xba));
        func_0208e5cc((char *) arg0 + 0x2500);
    }
}

void func_ov096_022a00b4(char *param)
{
    if (func_ov002_0220b57c(param + 0x2d9c) != 0) {
        if (func_0208e4bc(param + 0x2500) != 0) {
            int v1, v2;
            v1 = func_ov002_0220b5ec(param + 0x2d9c, 1);
            v2 = func_ov002_0220b59c(param + 0x2d9c, 1);
            func_ov002_0220a0b4(param + 0x2500, v1, v2);
        }
    } else {
        func_ov096_0229ddd8(param);
        func_ov002_02208090(param, 9);
        func_ov002_022080a0((void *) (param), 1);
    }
}

void func_ov096_022a0094(void *self)
{
    if (func_ov002_02208e28((char *) self + 0x2564) != 0) {
        func_ov096_0229fb4c(self);
    }
}

void func_ov096_022a0074(void *p)
{
    if (func_ov096_022a018c((int) p)) {
        func_ov096_0229ddd8((char *) p);
        func_ov002_02208098((void *) (p), 0x24);
    }
}
