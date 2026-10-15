/* func_ov003_02215798 @ 0x02215798, 0x5c bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;

void func_02010f5c(void *self);
void func_ov003_02215958(void *self);
int func_0200f554(void *self);
void func_ov003_02215918(void *self);
void func_02010d64(void *self);
int func_02073908(int a, int b);
void func_ov003_022157f4(void *self);
int func_02008258(void *self, int a);

typedef struct {
    unsigned char pad_00[0x7f0];
    int unk_7F0;
    unsigned char pad_7F4[0x8];
    int unk_7FC;
    int unk_800;
} UnkStruct_02215798;

void func_ov003_02215798(UnkStruct_02215798 *self)
{
    func_02010f5c(self);
    func_ov003_02215958(self);
    func_0200f554(self);
    func_ov003_02215918(self);
    func_02010d64(self);

    if (func_02073908(data_020ccf94, self->unk_800) != 0) {
        func_ov003_022157f4(self);
    } else {
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
}
