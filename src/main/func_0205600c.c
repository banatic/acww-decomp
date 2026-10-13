/* func_0205600c @ 0x0205600c, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Object {
    unsigned int unk_00;
} Object;

extern unsigned int data_020dd13c;
extern void func_02056390(Object *self);
extern void func_020edb3c(Object *self);

Object *func_0205600c(Object *self)
{
    self->unk_00 = (unsigned int) &data_020dd13c;
    func_02056390(self);
    func_020edb3c(self);
    return self;
}
