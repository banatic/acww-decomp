/* func_ov003_0221b9e4 @ 0x0221b9e4, 0x2c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov009_0226539c(void *self);
extern void func_020edf54(void *self) __attribute__((arm));

extern unsigned char data_ov003_02238434[];
extern unsigned char data_ov003_022384f8[];

void *func_ov003_0221b9e4(void *self)
{
    *(unsigned int *) self = (unsigned int) data_ov003_02238434;
    *(unsigned int *) ((char *) self + 0xec) = (unsigned int) data_ov003_022384f8;
    func_ov009_0226539c(self);
    func_020edf54(self);
    return self;
}
