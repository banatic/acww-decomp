/* func_ov049_02260454 @ 0x02260454, 0x38 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov049_02263544;
extern void *func_02072da4(void *);
extern void *func_ov049_022620d0(void *);
extern void *func_0202ee5c(void *);
extern void func_020edf54(void *);

void *func_ov049_02260454(void *obj)
{
    struct UnkStruct_02260454 {
        void *field_0;
        char pad0[0x654];
        char field_658[0xE4];
        char field_73c[1];
    } *self = obj;
    self->field_0 = &data_ov049_02263544;
    func_02072da4(&self->field_73c);
    func_ov049_022620d0(&self->field_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
