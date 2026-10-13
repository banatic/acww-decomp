/* func_020e99ac @ 0x020e99ac, 0x2c bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020e99ac {
    char pad_00[0x6c];
    int index;
};
struct UnkStruct_020e99ac_2 {
    int pad_00;
    struct UnkStruct_020e99ac *ptr;
};
extern struct UnkStruct_020e99ac_2 OSi_ThreadInfo;
extern int data_021fbe94;
extern int data_021fbe9c[];

void func_020e99ac(void)
{
    data_021fbe9c[OSi_ThreadInfo.ptr->index] = data_021fbe94;
}
