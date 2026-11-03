/* text_draw_6: 7 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02051b9c @ 0x02051b9c, 0x18 bytes, Thumb
 * func_02051b7c @ 0x02051b7c, 0x20 bytes, Thumb
 * func_02051b5c @ 0x02051b5c, 0x20 bytes, Thumb
 * func_02051b34 @ 0x02051b34, 0x28 bytes, Thumb
 * func_02051b20 @ 0x02051b20, 0x14 bytes, Thumb
 * func_02051b10 @ 0x02051b10, 0x10 bytes, Thumb
 * func_02051b00 @ 0x02051b00, 0x10 bytes, Thumb
 */

extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void func_020ee62c(void *obj);
extern unsigned char data_020da13c[];
extern unsigned char data_020dcf40[];
extern void func_020edf54(void *);
extern void func_020514dc(void);
extern void func_0206d83c(void);
extern void func_02051480(void);
extern void func_0205148c(void);

void *func_02051b7c(void *self);

void func_02051b9c(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_02051b7c((void *) result);
}

void *func_02051b7c(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_020dcf40);
    return self;
}

void *func_02051b5c(void *obj)
{
    volatile unsigned int *p = (volatile unsigned int *) obj;
    *p = (unsigned int) data_020dcf40;
    *p = (unsigned int) data_020da13c;
    func_020ee62c(obj);
    return obj;
}

void *func_02051b34(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_020dcf40;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}

int func_02051b20(void)
{
    func_020514dc();
    func_0206d83c();
    return 1;
}

int func_02051b10(void)
{
    func_02051480();
    return 1;
}

int func_02051b00(void)
{
    func_0205148c();
    return 1;
}
