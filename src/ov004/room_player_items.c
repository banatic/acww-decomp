/* room_player_items: 5 functions, module ov004
 * mwccarm 1.2/base -O4,s
 * func_ov004_02231b20 @ 0x02231b20, 0x18 bytes, Thumb
 * func_ov004_02231b00 @ 0x02231b00, 0x20 bytes, Thumb
 * func_ov004_02231ae0 @ 0x02231ae0, 0x20 bytes, Thumb
 * func_ov004_02231ab8 @ 0x02231ab8, 0x28 bytes, Thumb
 * func_ov004_02231aa8 @ 0x02231aa8, 0x10 bytes, Thumb
 */

extern int func_020edf70(int);
extern void *func_020ee660(void *);
extern void func_020ee62c(void *ptr);
extern void *const data_ov004_02255a38[];
extern void *const data_020da13c[];
extern void func_020edf54(void *p);
extern void func_ov004_022319ac(void);

void *func_ov004_02231b00(void *self);

void func_ov004_02231b20(void)
{
    int result;

    result = func_020edf70(0x50);
    if (result == 0) {
        return;
    }
    func_ov004_02231b00((void *) result);
}

void *func_ov004_02231b00(void *self)
{
    func_020ee660(self);
    *(void **) self = (void *) ((int *) data_020da13c);
    *(void **) self = (void *) ((int *) data_ov004_02255a38);
    return self;
}

void *func_ov004_02231ae0(void *p)
{
    volatile int *vp;
    vp = (volatile int *) p;
    *vp = (int) ((int *) data_ov004_02255a38);
    *vp = (int) ((int *) data_020da13c);
    func_020ee62c(p);
    return p;
}

void *func_ov004_02231ab8(const void **self)
{
    *self = data_ov004_02255a38;
    *self = data_020da13c;
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

int func_ov004_02231aa8(void)
{
    func_ov004_022319ac();
    return 1;
}
