/* func_ov066_02266950 @ 0x02266950, 0x1c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x3c];
    unsigned int flags;
} UnkStruct_02266950;

extern UnkStruct_02266950 *data_ov066_0226bdec;

void func_ov066_02266950(void)
{
    data_ov066_0226bdec->flags &= ~0x400;
}
