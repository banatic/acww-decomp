/* func_020a1628 @ 0x020a1628, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a1368(void);
extern void func_0209fb5c(int);
extern void func_0209e5e4(int);
extern int func_02050af8(int, int, int, int);
extern int data_021f3ba0;
extern int data_021dc7a8;
extern int data_021c8188;
extern int data_020d1c20[3];

int func_020a1628(void)
{
    int r4, r5, r6, r7;

    r4 = func_020a1368();
    r7 = (int) &data_021f3ba0;
    func_0209fb5c(r7);
    func_0209e5e4(r4);

    r6 = r4 + 0xc800;
    r5 = r7 - (int) &data_021dc7a8;
    r4 = r6 - r4;

    if (func_02050af8((int) &data_021c8188, data_020d1c20[0] + r5, r7, 4) == 1) {
        return 1;
    }
    if (func_02050af8((int) &data_021c8188, data_020d1c20[1] + r5, r7, 4) == 1) {
        return 1;
    }
    if (func_02050af8((int) &data_021c8188, data_020d1c20[2] + r4, r6, 1) == 1) {
        return 1;
    }

    return 0;
}
