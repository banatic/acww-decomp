/* func_ov136_0229d344 @ 0x0229d344, 0x54 bytes, Thumb, module ov136
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void);
extern void func_ov002_02209eb8(void *field);
extern int func_ov136_0229c574(void *self, int arg);
extern int func_ov002_02207f60(void *self);
extern void func_ov134_0229b220(void *field, int a, int b);
extern void func_ov002_0220ad18(void *field, int a);

typedef struct {
    char pad_00[0x94];
    char unk_94[0x64];
    char unk_F8[0x1CC];
    char unk_2C4;
} UnkStruct_0229d344;

int func_ov136_0229d344(UnkStruct_0229d344 *self)
{
    if (func_0206fe54()) {
        func_ov002_02209eb8(&self->unk_94);
    }
    if (func_ov136_0229c574(self, 1) == 0) {
        return 0;
    }
    func_ov134_0229b220(&self->unk_2C4, 0, func_ov002_02207f60(self));
    func_ov002_0220ad18(&self->unk_F8, func_ov002_02207f60(self));
    return 1;
}
