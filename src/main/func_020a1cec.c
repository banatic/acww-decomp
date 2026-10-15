/* func_020a1cec @ 0x020a1cec, 0x68 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021c8188;
extern int data_020d1bf0[];
extern int data_020d1c20[];

extern int func_02050974(int *a);
extern void func_02050948(int *a);
extern void MI_CpuFill8(int a, int b, int c);
extern int func_02050a84(int *a, int b, int c, int d);

int func_020a1cec(void *a, int b)
{
    int x = func_02050974(&data_021c8188);
    int v2 = data_020d1c20[b];
    int v1 = data_020d1bf0[b];

    if (x == 1) {
        func_02050948(&data_021c8188);
        return 1;
    }
    if (x == 4) {
        MI_CpuFill8(*(int *) ((char *) a + 0xb0), 0xff, v1);
        func_02050a84(&data_021c8188, v2, *(int *) ((char *) a + 0xb0), v1);
    } else if (x == 3) {
        // nothing
    } else {
        func_02050948(&data_021c8188);
        return 0;
    }
    return 3;
}
