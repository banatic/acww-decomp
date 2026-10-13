/* func_ov109_0229c418 @ 0x0229c418, 0x58 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02208d30(void *addr, int val);
extern void func_ov002_02207d24(void *addr, int val);
extern int func_ov109_0229ccb4(void *self, int param2);
extern void func_ov109_0229c470(void *self);
extern void func_ov109_0229c828(void *self);
extern void func_ov109_0229c564(void *self, int param3);

typedef struct {
    unsigned char pad_00[0x218c];
    unsigned char unk_218C;
    unsigned char pad_218D[0x533];
    unsigned char unk_26C0;
    unsigned char pad_26C1[0x313];
    unsigned char unk_29D4;
} UnkStruct_0229c418;

void func_ov109_0229c418(UnkStruct_0229c418 *self, unsigned char param2, int param3)
{
    self->unk_29D4 = param2;
    func_ov002_02208d30((void *) &self->unk_26C0, 1);
    if (func_ov109_0229ccb4(self, param2) != 0) {
        func_ov109_0229c470(self);
        func_ov109_0229c828(self);
        if (param3 == 0) {
            func_ov002_02207d24((void *) &self->unk_218C, 1);
        }
        func_ov109_0229c564(self, param3);
    }
}
