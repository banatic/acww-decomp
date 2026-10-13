/* func_ov046_022612cc @ 0x022612cc, 0x20 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *vtable;
} UnkStruct_022612cc;

extern int data_ov046_0226204c;
extern void func_0202eb20(UnkStruct_022612cc *, void *);
extern void func_020edb3c(UnkStruct_022612cc *);

UnkStruct_022612cc *func_ov046_022612cc(UnkStruct_022612cc *self)
{
    self->vtable = (void *) &data_ov046_0226204c;
    func_0202eb20(self, (void *) &data_ov046_0226204c);
    func_020edb3c(self);
    return self;
}
