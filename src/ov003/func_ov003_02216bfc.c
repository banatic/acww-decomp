/* func_ov003_02216bfc @ 0x02216bfc, 0xa0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int data_020ccf94;

typedef struct {
    unsigned char pad_00[0x98];
    int unk_98;
    unsigned char pad_9C[0x7f0 - 0x9c];
    int unk_7F0;
    unsigned char pad_7F4[0x7fc - 0x7f4];
    int unk_7FC;
    int unk_800;
} UnkStruct_02216bfc;

void func_02010f5c(UnkStruct_02216bfc *self);
int func_02073908(int, int);
void func_0201100c(UnkStruct_02216bfc *self);
void func_02010d64(UnkStruct_02216bfc *self);
int func_02011398(int, int);
void func_0201107c(UnkStruct_02216bfc *self, int *out);
void func_ov003_02216c9c(UnkStruct_02216bfc *self, int);
int func_0200f554(UnkStruct_02216bfc *self);
int func_02008258(UnkStruct_02216bfc *self, int);
void func_ov003_02216e5c(UnkStruct_02216bfc *self);

void func_ov003_02216bfc(UnkStruct_02216bfc *self)
{
    int a;
    int b;

    func_02010f5c(self);
    if (func_02073908(data_020ccf94, self->unk_800)) {
        func_0201100c(self);
        func_02010d64(self);
        a = func_02011398(self->unk_98, 0);
        func_0201107c(self, &a);
        func_ov003_02216c9c(self, 0);
    } else {
        if (func_0200f554(self)) {
            func_0201100c(self);
        }
        func_02010d64(self);
        b = func_02011398(self->unk_98, 0);
        func_0201107c(self, &b);
        self->unk_7FC = func_02008258(self, self->unk_7F0);
    }
    func_ov003_02216e5c(self);
}
