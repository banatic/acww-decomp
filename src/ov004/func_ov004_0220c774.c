/* func_ov004_0220c774 @ 0x0220c774, 0x6c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov004_0223b22c_unk(void *);
extern int func_ov004_0223b004_unk(int, void *, void *);
extern void func_ov004_0220ccf8(void *, int);
extern void func_ov004_0220d4ec_unk(void *, void *);

typedef struct {
    char pad_00[0x5c];
    int unk_5C;
    int unk_60;
    int unk_64;
    char pad_68[0x170 - 0x68];
    int unk_170;
    int unk_174;
    int unk_178;
    char pad_17C[0x18c - 0x17c];
    int unk_18C;
    char pad_190[0x250 - 0x190];
    char unk_250;
} UnkStruct_0220c774;

void func_ov004_0220c774(UnkStruct_0220c774 *self)
{
    int ret;
    ret = func_ov004_0223b22c_unk(self);
    if (ret) {
        int buffer[3];
        if (func_ov004_0223b004_unk(ret, &self->unk_250, buffer)) {
            self->unk_5C = self->unk_170;
            self->unk_60 = self->unk_174;
            self->unk_64 = self->unk_178;
            func_ov004_0220ccf8(self, 1);
            func_ov004_0220d4ec_unk(&self->unk_18C, self);
        } else {
            self->unk_5C = buffer[0];
            self->unk_60 = buffer[1];
            self->unk_64 = buffer[2];
        }
    }
}
