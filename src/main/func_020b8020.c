/* func_020b8020 @ 0x020b8020, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202fed4(void *);
extern char data_020e5810;

typedef struct {
    void *vtbl;
} Object;

Object *func_020b8020(Object *self)
{
    self->vtbl = &data_020e5810;
    func_0202fed4(self);
    return self;
}
