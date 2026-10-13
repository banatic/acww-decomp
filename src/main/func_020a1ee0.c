/* func_020a1ee0 @ 0x020a1ee0, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02050974(void *p);
extern void func_02050948(void *p);
extern void func_020509a8(void *p, int a, int b, int c);
extern void MI_CpuFill8(int a, int b, int c);

extern char data_021c8188;
extern int data_020d1c20[];
extern int data_020d1bf0[];

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char unk_A0;
    unsigned char pad_A1[0x13];
    int int_b4;
} UnkStruct_020a1ee0;

int func_020a1ee0(UnkStruct_020a1ee0 *base, int idx)
{
    int status = func_02050974(&data_021c8188);
    int arr1 = data_020d1c20[idx];
    int arr2 = data_020d1bf0[idx];

    if (status == 1) {
        func_02050948(&data_021c8188);
        return 1;
    } else if (status == 4) {
        MI_CpuFill8(base->int_b4, 0, arr2);
        func_020509a8(&data_021c8188, base->int_b4, arr2, arr1);
    } else if (status == 3) {
        // nothing
    } else {
        func_02050948(&data_021c8188);
        base->unk_A0 = 3;
    }
    return 3;
}
