/* func_02096718 @ 0x02096718, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02096718 {
    char pad_00[0x68];
    int unk_68;
};

extern struct UnkStruct_02096718 *data_020ccf94;
extern int func_0209641c(int a, int b);

extern unsigned char data_021d5684[];

int func_02096718(int param)
{
    int v;
    v = param;
    if (v == 4) {
        v = data_020ccf94->unk_68;
    }
    return func_0209641c((unsigned int) data_021d5684, v);
}
