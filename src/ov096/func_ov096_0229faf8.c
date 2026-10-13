/* func_ov096_0229faf8 @ 0x0229faf8, 0x54 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov096_0229c2dc(void *, int);
extern void func_ov096_0229c2ec(void *, int);
extern int func_ov096_0229f830(void *, unsigned char);
extern void func_ov096_0229cf84(void *, unsigned char);
extern void func_ov002_02208d30(void *, int);
extern int func_ov002_02208d18(void *);

typedef struct {
    char pad_00[0xb2];
    unsigned char unk_B2;
    char pad_B3[0x2899];
    char unk_294C[1];
} UnkStruct_0229faf8;

void func_ov096_0229faf8(UnkStruct_0229faf8 *param)
{
    func_ov096_0229c2dc(param, 0x00010000);
    if (func_ov096_0229f830(param, param->unk_B2) != 0) {
        func_ov002_02208d30(&param->unk_294C, 0x22);
        func_ov096_0229cf84(param, param->unk_B2);
        if (func_ov002_02208d18(&param->unk_294C) == 0) {
            func_ov096_0229c2ec(param, 0x00010000);
        }
    }
}
