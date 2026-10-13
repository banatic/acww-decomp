/* func_ov003_02233a14 @ 0x02233a14, 0x80 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233a14;
extern UnkStruct_02233a14 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02235b54(void *a, int b, int c);
extern short func_ov003_0223418c(int a, int b);

int func_ov003_02233a14(char *self, short *out)
{
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) == 0 || func_020a7278() != 0) {
        int r = func_ov003_02235b54(self, 0x50, 0xe38);
        if (r != 0) {
            *out = 0;
            *(char *) (self + 0x251) = 0xf;
            *(short *) (self + 0x240) = func_ov003_0223418c(*(short *) (self + 0x23a), r);
            *(int *) (self + 0x21c) |= 0xf00;
            *(int *) (self + 0x21c) += 1;
        }
        return r;
    }
    return 0;
}
