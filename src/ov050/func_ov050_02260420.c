/* func_ov050_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov050_02265a60[];
extern void func_ov050_022636b0(void *);
extern void func_0202ee5c(void *);

void *func_ov050_02260420(void *self)
{
    *(void **) self = data_ov050_02265a60;
    func_ov050_022636b0((char *) self + 0x658);
    func_0202ee5c(self);
    return self;
}
