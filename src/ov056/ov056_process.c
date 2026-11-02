/* ov056_process: 3 functions, module ov056
 * mwccarm 1.2/base -O4,s
 * func_ov056_0226046c @ 0x0226046c, 0x28 bytes, Thumb
 * func_ov056_0226044c @ 0x0226044c, 0x20 bytes, Thumb
 * func_ov056_02260420 @ 0x02260420, 0x2c bytes, Thumb
 */

struct UnkStruct_0226046c {
    void *volatile unk_00;
};

extern unsigned char data_ov056_022604b0[];
extern unsigned char data_020da13c[];
extern void func_020ee62c(void *);
extern void func_020edf54(void *);
extern void *func_020edf70(unsigned long);
extern void *func_020ee660(void *arg0);

void *func_ov056_0226046c(struct UnkStruct_0226046c *self)
{
    self->unk_00 = ((char *) data_ov056_022604b0);
    self->unk_00 = ((char *) data_020da13c);
    func_020ee62c(self);
    func_020edf54(self);
    return self;
}

void *func_ov056_0226044c(void *p)
{
    *(volatile unsigned int *) p = (unsigned int) data_ov056_022604b0;
    *(volatile unsigned int *) p = (unsigned int) data_020da13c;
    func_020ee62c(p);
    return p;
}

void *func_ov056_02260420(void)
{
    void *ret;
    volatile unsigned int *p;

    ret = func_020edf70(0x50);
    if (ret != 0) {
        func_020ee660((void *) ret);
        p = (volatile unsigned int *) ret;
        p[0] = (unsigned int) ((char *) data_020da13c);
        p[0] = (unsigned int) ((char *) data_ov056_022604b0);
    }
    return ret;
}
