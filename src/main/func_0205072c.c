/* func_0205072c @ 0x0205072c, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020f5958(char *);
extern void func_0209d34c(char *);
extern void func_0209d11c(char *);
extern void func_02055210(char *);
extern void func_0209d0a4(char *);

void *func_0205072c(void *self)
{
    char *b = (char *) self;
    func_020f5958(b);
    func_0209d34c(b + 0x48);
    func_0209d11c(b + 0x4c);
    func_02055210(b + 0x98);
    *(int *) (b + 0x40) = -1;
    *(int *) (b + 0x44) = 0;
    func_0209d0a4(b + 0x4c);
    *(int *) (b + 0x8c) = 0x1000;
    *(int *) (b + 0x90) = 0x1000;
    *(int *) (b + 0x94) = 0x1000;
    *(int *) (b + 0x150) = 0x1000;
    *(int *) (b + 0x154) = 0x1000;
    *(int *) (b + 0x158) = 0x1000;
    *(short *) (b + 0x15c) = 0;
    *(short *) (b + 0x15e) = 0;
    *(short *) (b + 0x160) = 0;
    *(int *) (b + 0x164) = 0x1f;
    return self;
}
