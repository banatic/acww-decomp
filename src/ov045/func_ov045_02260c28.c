/* func_ov045_02260c28 @ 0x02260c28, 0x6c bytes, Thumb, module ov045
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov045_02261380;
extern int func_0202ea80(int arg0, int arg1);
extern int func_ov045_02260644(void);

typedef struct {
    int unk_00;
    unsigned char unk_04;
} Result;

typedef struct {
    char pad_00[0xb4];
    int unk_B4;
} Param;

void func_ov045_02260c28(Param *param, Result *result)
{
    int v1, v2, v3;
    result->unk_00 = data_ov045_02261380;
    v1 = func_0202ea80(4, 0);
    v2 = func_0202ea80(5, 0);
    v3 = func_0202ea80(6, 0);
    if (v2 == 0 || v1 == 0) {
        if (v2 == 0) {
            result->unk_04 = 1;
        } else {
            result->unk_04 = 5;
        }
    } else {
        if (v3 == 0) {
            result->unk_04 = 0x11;
        } else {
            result->unk_04 = 0x19;
        }
    }
    if (((void) *(volatile int *) &param->unk_B4, func_ov045_02260644()) != 0) {
        result->unk_04 = 0x13;
    }
}
