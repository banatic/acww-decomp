/* func_ov004_0222a28c @ 0x0222a28c, 0x5c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;

void func_ov004_0222a390(void *self);
void func_02010f5c(void *self);
void func_0201100c(void *self);
void func_02010d64(void *self);
void func_02010ca4(void *self);
void func_02010d64(void *self);
int func_02073908(int a, int b);
void func_ov004_0222a2e8(void *self);
int func_02008258(void *self, int a);

typedef struct {
    unsigned char pad_00[0x7f0];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    int unk_800;
} Obj_020d82b4;

void func_ov004_0222a28c(Obj_020d82b4 *self)
{
    func_ov004_0222a390(self);
    func_02010f5c(self);
    func_0201100c(self);
    func_02010d64(self);
    func_02010ca4(self);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov004_0222a2e8(self);
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}
