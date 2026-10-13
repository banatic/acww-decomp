/* func_ov046_02260ddc @ 0x02260ddc, 0x58 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_02073d90(void *p);
extern short *func_0209d358(int a, int b);
extern int func_020b1558(void);
extern void *data_020ccf94;

struct UnkStruct_02260ddc {
    char pad_00[0xDC];
    int unk_DC;
};

void func_ov046_02260ddc(struct UnkStruct_02260ddc *self)
{
    if (func_02073d90(data_020ccf94) || *(short *) func_0209d358(0, 0x4A)) {
        if (func_020b1558() < 16) {
            self->unk_DC = 0x13;
        } else {
            self->unk_DC = 0x10;
        }
    } else {
        if (func_020b1558() < 16) {
            self->unk_DC = 0x14;
        } else {
            self->unk_DC = 1;
        }
    }
}
