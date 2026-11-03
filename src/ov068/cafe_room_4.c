/* cafe_room_4: 4 functions, module ov068
 * mwccarm 1.2/base -O4,s
 * func_ov068_0227520c @ 0x0227520c, 0x1c bytes, Thumb
 * func_ov068_022751c4 @ 0x022751c4, 0x48 bytes, Thumb
 * func_ov068_02275184 @ 0x02275184, 0x40 bytes, Thumb
 * func_ov068_02275140 @ 0x02275140, 0x44 bytes, Thumb
 */

extern int func_020edf70(int);
extern void *func_ov004_0222c87c(void *p);
extern void *func_02055210(void *p);
extern int func_ov004_0222c548(void *p);
extern void func_ov004_0222c398(void *p);
extern int data_ov068_022788b0;
extern char data_ov068_02277f3c;
extern void func_ov004_0222c394(char *);
extern int func_ov004_0222c538(char *);
extern void *func_020551e0(char *);
extern void *func_ov004_0222c7a0(char *);
extern void func_020edf54(void *);

void *func_ov068_022751c4(void *p);

void func_ov068_0227520c(void)
{
    void *condition_value_23;
    condition_value_23 = (void *) (func_020edf70(0x3fc));
    if (condition_value_23 != 0) {
        func_ov068_022751c4(condition_value_23);
    }
}

void *func_ov068_022751c4(void *p)
{
    func_ov004_0222c87c(p);
    *(int **) p = ((int *) &data_ov068_02277f3c);
    func_02055210((char *) p + 0x29c);
    func_ov004_0222c548((char *) p + 0x354);
    func_ov004_0222c398((char *) p + 0x3f8);
    data_ov068_022788b0 = 0;
    return p;
}

char *func_ov068_02275184(char *self)
{
    *(char **) self = &data_ov068_02277f3c;
    func_ov004_0222c394(self + 0x3f8);
    func_ov004_0222c538(self + 0x354);
    func_020551e0(self + 0x29c);
    func_ov004_0222c7a0(self);
    return self;
}

void *func_ov068_02275140(void *self)
{
    *(void **) self = &data_ov068_02277f3c;
    func_ov004_0222c394((char *) ((char *) self + 0x3f8));
    func_ov004_0222c538((char *) ((char *) self + 0x354));
    func_020551e0((char *) ((char *) self + 0x29c));
    func_ov004_0222c7a0((char *) self);
    func_020edf54(self);
    return self;
}
