/* func_ov003_0220ffc0 @ 0x0220ffc0, 0x50 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02210094(int *src, int *dst);
extern int func_ov003_022100c4(void *self, int *out, int a, int b, int c);

typedef struct {
    char pad_00[0x7f0];
    int unk_7F0;
    char pad_7F4[0xfc];
    int unk_8F0;
    char pad_8F4[0x390];
    short unk_C84;
} UnkStruct_0220ffc0;

void func_ov003_0220ffc0(UnkStruct_0220ffc0 *self, int param)
{
    if (self->unk_7F0 == 0x66) {
        self->unk_C84 = (short) param;
    } else {
        int tmp[2];
        int out[2];
        tmp[0] = 0;
        tmp[1] = 0;
        func_ov003_02210094(&self->unk_8F0, tmp);
        out[0] = tmp[0];
        out[1] = tmp[1];
        func_ov003_022100c4(self, out, 0, 6, param);
    }
}
