/* func_ov045_02260420 @ 0x02260420, 0x28 bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_02260420_2 {
    char pad_00;
} UnkStruct_02260420_2;

typedef struct UnkStruct_02260420 {
    void *vtable;
    unsigned char pad_04[0x688];
    UnkStruct_02260420_2 sub;
} UnkStruct_02260420;

extern char data_ov045_022614f0;
extern void *func_ov045_02260d34(UnkStruct_02260420_2 *ptr);
extern void *func_0202ee5c(UnkStruct_02260420 *self);

UnkStruct_02260420 *func_ov045_02260420(UnkStruct_02260420 *self)
{
    self->vtable = &data_ov045_022614f0;
    func_ov045_02260d34(&self->sub);
    func_0202ee5c(self);
    return self;
}
