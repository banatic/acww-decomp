/* func_ov105_0229c758 @ 0x0229c758, 0xd4 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStruct_0229c758 {
    unsigned char pad_00[0x2ba];
    unsigned char unk_2BA;
    unsigned char pad_2BB[0x21e9];
    unsigned char unk_24A4;
} UnkStruct_0229c758;

extern int func_ov105_0229c320(UnkStruct_0229c758 *self, int arg);
extern int func_ov105_0229d76c(UnkStruct_0229c758 *self, unsigned char field);
extern void func_ov105_0229c9ac(UnkStruct_0229c758 *self, int a, int b);
extern int func_ov105_0229d75c(UnkStruct_0229c758 *self, unsigned char field);
extern void func_ov105_0229c8b4(UnkStruct_0229c758 *self, int a, int b);
extern int func_ov105_0229d73c(UnkStruct_0229c758 *self, unsigned char field);
extern int func_ov105_0229d750(UnkStruct_0229c758 *self, unsigned char field);
extern void func_ov105_0229c888(UnkStruct_0229c758 *self, int a);
extern void func_ov105_0229c82c(UnkStruct_0229c758 *self, int a);
extern void func_ov002_0220a374(void *ptr, int val);
extern void func_0208e4c0(void *ptr, int val);

int func_ov105_0229c758(UnkStruct_0229c758 *self, int param1, int param2)
{
    unsigned char field = self->unk_2BA;

    func_ov105_0229c320(self, 0x30);

    if (param1 == 0) {
        return 0;
    }

    if (func_ov105_0229d76c(self, self->unk_2BA) != 0) {
        func_ov105_0229c9ac(self, param1, param2);
    } else if (func_ov105_0229d75c(self, self->unk_2BA) != 0) {
        func_ov105_0229c8b4(self, param1, param2);
        if (func_ov105_0229d73c(self, self->unk_2BA) != 0 && param2 == 1) {
            func_ov002_0220a374(&self->unk_24A4, 1);
        }
    } else {
        if (func_ov105_0229d750(self, self->unk_2BA) != 0) {
            func_ov105_0229c888(self, param1);
        } else {
            if (func_ov105_0229d73c(self, self->unk_2BA) != 0) {
                func_ov105_0229c82c(self, param1);
                if (func_ov105_0229d73c(self, self->unk_2BA) == 0 && param2 == 1) {
                    func_0208e4c0(&self->unk_24A4, 4);
                }
            }
        }
    }

    return (field != self->unk_2BA) ? 1 : 0;
}
