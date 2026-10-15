/* func_ov054_022622a8 @ 0x022622a8, 0x68 bytes, Thumb, module ov054
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_022622a8 {
    char pad_00[0x350];
    char sub1[0x214];
    char sub2[0x2a8];
    int unk_80C;
};

extern unsigned char data_ov054_0226297c[];
extern int func_ov054_02260474(void *self);
int func_ov054_02262494(struct UnkStruct_022622a8 *self);
void func_ov054_02262528(struct UnkStruct_022622a8 *self, int n);
void func_0201af1c(void *ptr, unsigned char val);
int func_02019e00(void *ptr);
int func_02019de8(void *ptr);

int func_ov054_022622a8(struct UnkStruct_022622a8 *self)
{
    func_ov054_02260474(self);
    if (func_ov054_02262494(self) != 0) {
        func_ov054_02262528(self, 3);
        func_0201af1c(&self->sub1, data_ov054_0226297c[self->unk_80C]);
        return 1;
    } else {
        if (func_02019e00(&self->sub2) == 6) {
            if (func_02019de8(&self->sub2) != 0) {
                func_ov054_02262528(self, 6);
            }
        }
        return 1;
    }
}
