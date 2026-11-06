/* session_players_3: 4 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02096718 @ 0x02096718, 0x20 bytes, Thumb
 * func_020966fc @ 0x020966fc, 0x1c bytes, Thumb
 * func_020966e0 @ 0x020966e0, 0x1c bytes, Thumb
 * func_020966c4 @ 0x020966c4, 0x1c bytes, Thumb
 */

struct UnkStruct_02096718 {
    char pad_00[0x68];
    int unk_68;
};

extern int func_0209641c(int a, int b);
extern unsigned char data_021d5684[];
extern int data_020ccf94;
extern int data_020d1864[];
extern int func_020738bc(int, int);
extern unsigned int data_020d1874[];
extern int data_020d1884[];

int func_02096718(int param)
{
    int v;
    v = param;
    if (v == 4) {
        v = (*(struct UnkStruct_02096718 **) &data_020ccf94)->unk_68;
    }
    return func_0209641c((unsigned int) data_021d5684, v);
}

int func_020966fc(int param)
{
    return func_020738bc(data_020ccf94, data_020d1864[param]);
}

int func_020966e0(int param)
{
    return func_020738bc((*(unsigned int *) &data_020ccf94), data_020d1874[param]);
}

int func_020966c4(int param)
{
    return func_020738bc(data_020ccf94, data_020d1884[param]);
}
