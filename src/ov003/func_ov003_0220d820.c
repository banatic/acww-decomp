/* func_ov003_0220d820 @ 0x0220d820, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;
extern int func_02073908(int a, int b);
extern void func_020984fc(int a);
extern unsigned short *func_02099728(void);
extern void func_0200f1a4(void *self, int a, unsigned short b);
extern void func_0209129c(int a);

typedef struct {
    char pad_00[0x7d4];
    int unk_7D4;
    char pad_7D8[0x28];
    int unk_800;
} UnkStruct_0220d820;

void func_ov003_0220d820(UnkStruct_0220d820 *self)
{
    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        unsigned short *p;
        func_020984fc(self->unk_800);
        p = func_02099728();
        if (p != 0) {
            func_0200f1a4(self, 3, *p);
        }
    }
    if (self->unk_7D4 != -1) {
        func_0209129c(self->unk_7D4);
    }
}
