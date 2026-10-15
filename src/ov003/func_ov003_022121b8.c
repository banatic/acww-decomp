/* func_ov003_022121b8 @ 0x022121b8, 0x54 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov003_02212270(unsigned char *, unsigned char *, unsigned char *, unsigned char *, unsigned char *);
extern int func_ov003_022122ac(unsigned char *, int, int *, int, int);

void func_ov003_022121b8(unsigned char *obj, int param2)
{
    unsigned char buf[4];

    func_ov003_02212270(obj + 0x8f0, buf, buf + 1, buf + 2, buf + 3);
    obj[0x16c] = buf[3];

    if (buf[0] == 0) {
        int arr[2];

        arr[0] = buf[1];
        arr[1] = buf[2];
        func_ov003_022122ac(obj, 0, arr, 6, param2);
    }
}
