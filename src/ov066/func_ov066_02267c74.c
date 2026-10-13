/* func_ov066_02267c74 @ 0x02267c74, 0x3c bytes, ARM, module ov066
 * mwccarm 1.2/base -O4,p
 */

typedef struct {
    char pad_00[0xC];
    signed int flag : 1;
} UnkStruct_02267c74;

extern UnkStruct_02267c74 *data_ov066_0226bdf0;
extern void func_ov066_02267be0(void);

void func_ov066_02267c74(void)
{
    if (data_ov066_0226bdf0->flag) {
        return;
    }
    func_ov066_02267be0();
}
