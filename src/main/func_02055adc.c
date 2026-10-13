/* func_02055adc @ 0x02055adc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} Object;

extern void func_020edb3c(void *obj);

extern unsigned char data_020dd10c[];

void *func_02055adc(void *self)
{
    Object *obj = (Object *) self;
    obj->vtable = (void *) data_020dd10c;
    func_020edb3c(self);
    return (char *) self + 0;
}
