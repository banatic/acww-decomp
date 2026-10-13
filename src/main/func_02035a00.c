/* func_02035a00 @ 0x02035a00, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} Object;

extern void func_020edb3c(void *);

extern unsigned char data_020da314[];

void *func_02035a00(Object *self)
{
    self->vtable = (void *) data_020da314;
    func_020edb3c(self);
    return self;
}
