/* func_ov066_02267be0 @ 0x02267be0, 0x2c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned int unk_04;
    unsigned int unk_08;
    unsigned int unk_0C;
    unsigned int unk_10;
} UnkStruct_02267be0;

extern UnkStruct_02267be0 *data_ov066_0226bdf0;
extern void OS_CancelAlarm(void *);

void func_ov066_02267be0(void)
{
    data_ov066_0226bdf0->unk_0C &= ~2;
    OS_CancelAlarm(&data_ov066_0226bdf0->unk_10);
}
