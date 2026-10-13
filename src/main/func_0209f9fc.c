/* func_0209f9fc @ 0x0209f9fc, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020edf70(int size);
extern void func_020ee660(void);
static void sub_0209f538(void *ptr);

extern unsigned char data_020da13c[];
extern unsigned char data_020e3708[];

void *func_0209f9fc(void)
{
    void *obj;

    obj = func_020edf70(0xa4);
    if (obj != 0) {
        func_020ee660();
        *(volatile void **) obj = (void *) data_020da13c;
        *(volatile void **) obj = (void *) data_020e3708;
        sub_0209f538((char *) obj + 0x54);
    }
    return obj;
}

static void sub_0209f538(void *ptr)
{
    (void) ptr;
}
