/* func_ov068_0226e1ac @ 0x0226e1ac, 0x2c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov068_0226e5d4(void *p);
extern void func_0202ee5c(void *p);
extern void func_020edf54(void *p);

typedef struct {
    void *vtable;
    char pad_04[0x658 - 4];
    int unk_658;
} UnkStruct_0226e1ac;

extern unsigned char data_ov068_02277574[];

UnkStruct_0226e1ac *func_ov068_0226e1ac(UnkStruct_0226e1ac *self)
{
    self->vtable = (void *) data_ov068_02277574;
    func_ov068_0226e5d4(&self->unk_658);
    func_0202ee5c(self);
    func_020edf54(self);
    return self;
}
