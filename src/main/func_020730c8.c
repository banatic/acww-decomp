/* func_020730c8 @ 0x020730c8, 0x38 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void OS_Terminate(void);
extern char SDK_OVERLAY_ov066_ID;

struct UnkStruct_020730c8 {
    unsigned int word;
    unsigned char flag;
};

extern struct UnkStruct_020730c8 data_021d11c4;

void func_020730c8(void)
{
    int v;
    unsigned int same;

    if (data_021d11c4.flag) {
        v = -1;
    } else {
        v = (int) data_021d11c4.word;
    }

    if ((int) &SDK_OVERLAY_ov066_ID == v) {
        same = 1;
    } else {
        same = 0;
    }

    if (same == 0) {
        OS_Terminate();
    }
}
