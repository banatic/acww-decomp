/* func_0205de24 @ 0x0205de24, 0x4c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205dde8(unsigned char *);
extern int func_0205de10(void *p);
extern int func_021077e8(int x);
extern int func_020b9eec(void *obj, int val, int flag);

int func_0205de24(void *self)
{
    void *obj;
    unsigned char b;
    unsigned int f1;
    unsigned int f2;

    obj = func_0205dde8(self);
    b = ((unsigned char *) obj)[0xd];
    f1 = (b == 2) ? 1 : 0;
    if (f1) {
        return 1;
    }
    f2 = (b == 1) ? 1 : 0;
    if (f2 == 0) {
        func_020b9eec(obj, func_021077e8(func_0205de10(self)), 1);
    }
    return 0;
}
