/* func_ov077_02278ba0 @ 0x02278ba0, 0x5c bytes, Thumb, module ov077
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int);
extern void func_020683e4(void *a, int b, void *c, void *d);

struct UnkStruct_02278ba0 {
    unsigned char pad_00[0x1e];
    unsigned char flag;
    unsigned char pad_1F[0x40 - 0x1f];
    void *unk_40;
    unsigned char pad_44[0xb8 - 0x44];
    unsigned char *arr;
};

extern unsigned char data_ov077_02279938;

void func_ov077_02278ba0(struct UnkStruct_02278ba0 *self)
{
    if (self->flag == 0x17) {
        unsigned char cur = (unsigned char) func_020644cc(0x10);
        if (cur == self->arr[0x718]) {
            cur++;
            if (cur == 0x10) {
                cur = 0;
            }
        }
        self->arr[0x718] = cur;
        {
            unsigned char v = self->arr[0x718];
            func_020683e4(self->unk_40, 0, &v, &data_ov077_02279938);
        }
    }
}
