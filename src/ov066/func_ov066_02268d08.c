/* func_ov066_02268d08 @ 0x02268d08, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern int OS_DisableInterrupts(void);
extern void OS_RestoreInterrupts(int);

typedef struct {
    unsigned char pad_00[0xc0];
    unsigned int : 2;
    signed int b : 1;
    signed int c : 1;
} UnkStruct_02268d08;

extern UnkStruct_02268d08 *data_ov066_0226bdf4;

void func_ov066_02268d08(void)
{
    int old = OS_DisableInterrupts();
    if (data_ov066_0226bdf4->c == 0) {
        data_ov066_0226bdf4->b = 1;
    }
    OS_RestoreInterrupts(old);
}
