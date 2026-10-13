/* func_ov049_0226171c @ 0x0226171c, 0x48 bytes, Thumb, module ov049
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int arg);
extern int func_ov049_02260780(unsigned int a, unsigned int b);
extern unsigned int data_ov049_02262dec[];

struct UnkStruct_0226171c {
    unsigned char pad_00[0xb0];
    unsigned int unk_B0;
};

int func_ov049_0226171c(struct UnkStruct_0226171c *param, int idx)
{
    int n = 0;
    switch (idx) {
        case 0:
            n = func_020644cc(3);
            break;
        case 1:
            n = func_020644cc(3) + 3;
            break;
        case 2:
            n = func_020644cc(4) + 6;
            break;
        default:
            break;
    }
    return func_ov049_02260780(param->unk_B0, data_ov049_02262dec[n]);
}
