/* func_ov111_022a06c8 @ 0x022a06c8, 0x40 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021fbdd8;
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov111_0229f5bc(void *self);
extern void func_ov111_0229fd08(void *self);
extern void func_ov111_0229efb8(void *self, int arg);

typedef struct {
    unsigned char pad_00[0x9F];
    unsigned char unk_9F;
    unsigned char unk_A0;
} UnkStruct_022a06c8;

void func_ov111_022a06c8(void *self)
{
    if (data_021fbdd8 == 0) {
        func_ov002_02208098((void *) (self), 0);
        if (((UnkStruct_022a06c8 *) self)->unk_9F == ((UnkStruct_022a06c8 *) self)->unk_A0) {
            func_ov111_0229efb8(self, 1);
        }
    } else {
        func_ov111_0229f5bc(self);
    }
    func_ov111_0229fd08(self);
}
