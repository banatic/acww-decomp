/* library_overlay: 3 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02073100 @ 0x02073100, 0x38 bytes, Thumb
 * func_020730c8 @ 0x020730c8, 0x38 bytes, Thumb
 * func_02073090 @ 0x02073090, 0x38 bytes, Thumb
 */

struct UnkStruct_02073100 {
    unsigned int word;
    unsigned char flag;
};

struct UnkStruct_020730c8 {
    unsigned int word;
    unsigned char flag;
};

struct UnkStruct_02073090 {
    unsigned int word;
    unsigned char flag;
};

extern void OS_Terminate(void);
extern char SDK_OVERLAY_ov065_ID;
extern struct UnkStruct_02073100 data_021d11c4;
extern char SDK_OVERLAY_ov066_ID;
extern char SDK_OVERLAY_ov067_ID;

void func_02073100(void)
{
    int v;
    unsigned int same;

    if (data_021d11c4.flag) {
        v = -1;
    } else {
        v = (int) data_021d11c4.word;
    }

    if ((int) &SDK_OVERLAY_ov065_ID == v) {
        same = 1;
    } else {
        same = 0;
    }

    if (same == 0) {
        OS_Terminate();
    }
}

void func_020730c8(void)
{
    int v;
    unsigned int same;

    if ((*(struct UnkStruct_020730c8 *) &data_021d11c4).flag) {
        v = -1;
    } else {
        v = (int) (*(struct UnkStruct_020730c8 *) &data_021d11c4).word;
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

void func_02073090(void)
{
    int v;
    unsigned int same;

    if ((*(struct UnkStruct_02073090 *) &data_021d11c4).flag) {
        v = -1;
    } else {
        v = (int) (*(struct UnkStruct_02073090 *) &data_021d11c4).word;
    }

    if ((int) &SDK_OVERLAY_ov067_ID == v) {
        same = 1;
    } else {
        same = 0;
    }

    if (same == 0) {
        OS_Terminate();
    }
}
