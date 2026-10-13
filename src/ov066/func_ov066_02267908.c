/* func_ov066_02267908 @ 0x02267908, 0x44 bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

extern struct UnkStruct_02267908;
struct UnkStruct_02267908 {
    char pad_00[0xc0];
    unsigned int unk_C0;
};
extern struct UnkStruct_02267908 *data_ov066_0226bdf4;
extern char *data_ov066_0226bdf0;
extern void OS_CancelAlarm(void *p);
extern void func_ov066_02267be0(void);

void func_ov066_02267908(void)
{
    data_ov066_0226bdf4->unk_C0 |= 0x100;
    OS_CancelAlarm((char *) data_ov066_0226bdf0 + 0x3c);
    func_ov066_02267be0();
}
