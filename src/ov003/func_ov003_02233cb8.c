/* func_ov003_02233cb8 @ 0x02233cb8, 0xb0 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_02233cb8;
extern UnkStruct_02233cb8 *data_020ccf94;
extern int func_02073dd4(void *a, int b);
extern int func_020a7278(void);
extern int func_ov003_02233c70(int a, int b);

void func_ov003_02233cb8(char *self, short *out)
{
    *out = *out + 1;
    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0 && func_020a7278() == 0) {
        int *s = (int *) (self + 0x204);
        int *d = (int *) (self + 0x1d4);
        if (s[0] != d[0] || s[2] != d[2]) {
            *(char *) (self + 0x251) = 4;
            *out = 0;
            *(char *) (self + 0x24c) = 1;
        }
    } else if (*out >= *(short *) (self + 0x232)) {
        int base = *(short *) (self + 0x23a);
        int t = func_ov003_02233c70(0xc, 1);
        *(short *) (self + 0x240) = t + base;
        *(int *) (self + 0x21c) |= 0xf00;
        *(char *) (self + 0x251) = 3;
        *out = 0;
    }
}
