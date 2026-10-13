/* func_ov119_0229b828 @ 0x0229b828, 0x5c bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov119_0229a420(void *self, int param);
extern int func_ov002_02208ae4(void *arg);
extern int func_ov002_02208ad8(void *arg, unsigned char byte);
extern void func_ov002_0220a0b4(void *ptr, int a, int b);
extern void func_ov002_0220a374(void *ptr, int val);

typedef struct {
    char pad_00[0xae];
    unsigned char flag; // offset 0xae
    char pad_AF[0xdc - 0xaf];
    char unk_DC[1]; // offset 0xdc
    char pad_DD[0xda8 - 0xdd];
    char obj[1]; // offset 0xda8
} UnkStruct_0229b828;

void func_ov119_0229b828(UnkStruct_0229b828 *self)
{
    int v1;
    int v2;

    if (func_ov119_0229a420(self, 0x10) != 0) {
        self->flag = 2;
    } else {
        self->flag = 0;
    }

    v1 = func_ov002_02208ae4(self->unk_DC);
    v2 = func_ov002_02208ad8(self->unk_DC, self->flag);
    func_ov002_0220a0b4(self->obj, v1, v2);
    func_ov002_0220a374(self->obj, 7);
}
