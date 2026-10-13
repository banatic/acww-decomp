/* func_020a6db0 @ 0x020a6db0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_020a6db0;
typedef struct UnkStruct_020a6db0 UnkStruct_020a6db0;
struct UnkStruct_020a6db0 {
    unsigned char pad_00[0x64];
    void *unk_64;
};
extern UnkStruct_020a6db0 *data_020ccf94;

extern int func_02073dd4(UnkStruct_020a6db0 *self, void *field);
extern int func_020733f8(UnkStruct_020a6db0 *self);
extern void func_020a753c(void);
extern void func_020a7394(void *field, int a, int b, int c, int d);
extern int func_02073d90(UnkStruct_020a6db0 *self);
extern void func_020a7880(unsigned char *local);
extern void func_020a7850(unsigned char *local, int a, int b, int c, int d);
extern void func_02073820(UnkStruct_020a6db0 *self);
extern void func_020737f0(UnkStruct_020a6db0 *self, unsigned char *local, int a);
extern void func_02073770(UnkStruct_020a6db0 *self, int a, int b);
extern void func_020a7870(unsigned char *local);
extern void func_020a7360(void *field, int a, int b, int c, int d);

void func_020a6db0(void)
{
    UnkStruct_020a6db0 *self = data_020ccf94;
    void *field = self->unk_64;

    if (func_02073dd4(self, field) != 0) {
        if (func_020733f8(self) != 0) {
            func_020a753c();
            func_020a7394(field, 0x3f, 1, 0, 2);
            if (func_02073d90(self) != 0) {
                if (field != 0) {
                    unsigned char local[8];
                    UnkStruct_020a6db0 *self2;
                    func_020a7880(local);
                    func_020a7850(local, 0x3f, 1, 0, 2);
                    self2 = data_020ccf94;
                    func_02073820(self2);
                    func_020737f0(self2, local, 2);
                    func_02073770(self2, 0xb, 0);
                    func_020a7870(local);
                } else {
                    func_020a7360(field, 0x3f, 1, 0, 2);
                }
            }
        }
    }
}
