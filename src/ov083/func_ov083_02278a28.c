/* func_ov083_02278a28 @ 0x02278a28, 0x2c bytes, Thumb, module ov083
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov083_0227928c;
extern void func_ov083_02278d64(void *);
extern void func_0202ee5c(void *);
extern void func_020edf54(void *);

struct TheStruct {
    void *vtbl;
    char pad_04[0x65c - 4];
    char sub;
};

struct TheStruct *func_ov083_02278a28(struct TheStruct *self)
{
    self->vtbl = &data_ov083_0227928c;
    func_ov083_02278d64(&self->sub);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
