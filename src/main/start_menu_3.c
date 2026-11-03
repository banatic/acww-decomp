/* start_menu_3: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_0209f9fc @ 0x0209f9fc, 0x34 bytes, Thumb
 * func_0209f9e8 @ 0x0209f9e8, 0x14 bytes, Thumb
 * func_0209f9e4 @ 0x0209f9e4, 0x4 bytes, Thumb
 */

extern void *func_020edf70(int size);
extern void *func_020ee660(void *);
extern void *func_0209f538(void *ptr);
extern unsigned char data_020da13c[];
extern unsigned char data_020e3708[];
extern void func_0209f4fc(void *a, void *b);

void *func_0209f9fc(void)
{
    void *obj;

    obj = func_020edf70(0xa4);
    if (obj != 0) {
        func_020ee660(obj);
        *(volatile void **) obj = (void *) data_020da13c;
        *(volatile void **) obj = (void *) data_020e3708;
        func_0209f538((char *) obj + 0x54);
    }
    return obj;
}

int func_0209f9e8(void *arg0)
{
    void *r1;
    void *r0;

    r1 = arg0;
    r0 = (char *) arg0 + 0x54;
    func_0209f4fc(r0, r1);
    return 1;
}

int func_0209f9e4(void)
{
    return 1;
}
