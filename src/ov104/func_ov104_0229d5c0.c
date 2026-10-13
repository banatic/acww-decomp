/* func_ov104_0229d5c0 @ 0x0229d5c0, 0x64 bytes, Thumb, module ov104
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb6];
    unsigned char unk_B6;
    unsigned char pad_B7;
    unsigned char unk_B8;
} GameData;

extern int func_ov104_0229da80(GameData *self, unsigned char c);
extern int func_ov104_0229da70(GameData *self, unsigned char c);
extern int func_ov104_0229d7bc(GameData *self, unsigned char c);
extern void func_ov002_02207cf0(void *ptr);
extern void func_ov002_02207cf8(void *ptr);

void func_ov104_0229d5c0(GameData *self)
{
    if (func_ov104_0229da80(self, self->unk_B8) != 0 || func_ov104_0229da70(self, self->unk_B8) != 0) {
        if (func_ov104_0229d7bc(self, self->unk_B8) != 0) {
            func_ov002_02207cf0((char *) self + 0x23b8);
        } else {
            self->unk_B6 = self->unk_B8;
            func_ov002_02207cf8((char *) self + 0x23b8);
        }
    } else {
        func_ov002_02207cf0((char *) self + 0x23b8);
    }
}
