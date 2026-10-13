/* func_ov049_022620d0 @ 0x022620d0, 0x18 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern void func_0202eb20(void *self, void *arg);
extern char data_ov049_022634b4;

typedef struct {
    void *vtable;
} UnkStruct_022620d0;

UnkStruct_022620d0 *func_ov049_022620d0(UnkStruct_022620d0 *self)
{
    self->vtable = &data_ov049_022634b4;
    func_0202eb20(self, &data_ov049_022634b4);
    return self;
}
