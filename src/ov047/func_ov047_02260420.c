/* func_ov047_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov047_02261978(void *);
extern void func_0202ee5c(void *);

struct UnkStruct_02260420 {
    void *vtable;
    char pad_04[0x654];
    char sub[1];
};

extern unsigned char data_ov047_02262ca4[];

struct UnkStruct_02260420 *func_ov047_02260420(struct UnkStruct_02260420 *self)
{
    self->vtable = (void *) data_ov047_02262ca4;
    func_ov047_02261978(&self->sub);
    func_0202ee5c(self);
    return self;
}
