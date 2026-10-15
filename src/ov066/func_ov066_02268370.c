/* func_ov066_02268370 @ 0x02268370, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned long fc0_0 : 7;
    signed long fc0_7 : 1;
} UnkStruct_02268370;

extern UnkStruct_02268370 *data_ov066_0226bdf4;

extern void func_ov066_0226a00c(void);
extern void func_ov066_02269748(int a);

void func_ov066_02268370(int a)
{
    if (data_ov066_0226bdf4->fc0_7) {
        func_ov066_0226a00c();
    } else {
        func_ov066_02269748(a);
    }
}
