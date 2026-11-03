/* taxi_driver: 4 functions, module ov051
 * mwccarm 1.2/base -O4,s
 * func_ov051_02260490 @ 0x02260490, 0x18 bytes, Thumb
 * func_ov051_02260474 @ 0x02260474, 0x1c bytes, Thumb
 * func_ov051_02260448 @ 0x02260448, 0x2c bytes, Thumb
 * func_ov051_02260420 @ 0x02260420, 0x28 bytes, Thumb
 */

extern unsigned int *data_ov051_02261b80;
extern int func_020164a0(int a, int b);
extern char data_ov051_0226193c;
extern void *func_ov051_02261058(char *p);
extern void *func_0202ee5c(char *p);
extern void func_020edf54(char *p);

unsigned int func_ov051_02260490(void)
{
    return (data_ov051_02261b80[100] << 4) >> 16;
}

int func_ov051_02260474(void)
{
    return func_020164a0((*(int *) &data_ov051_02261b80) + 0x334, 0);
}

char *func_ov051_02260448(char *p)
{
    *(char **) p = &data_ov051_0226193c;
    func_ov051_02261058(p + 0x658);
    func_0202ee5c(p);
    func_020edf54(p);
    return p;
}

void *func_ov051_02260420(void *self)
{
    *(unsigned int *) self = (unsigned int) ((int *) &data_ov051_0226193c);
    func_ov051_02261058((char *) ((char *) self + 0x658));
    func_0202ee5c((char *) self);
    return self;
}
