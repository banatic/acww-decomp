/* func_ov003_02217608 @ 0x02217608, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short func_ov003_022177d0(int, unsigned char *, int *, int *, unsigned char *);
extern int func_ov003_02217838(int, int, int, int, int, int, int, int);

void func_ov003_02217608(int a, int b)
{
    unsigned char arr[4];
    int v1;
    int v2;
    int sel;

    func_ov003_022177d0(a + 0x8f0, arr, &v1, &v2, arr + 2);
    switch (arr[0] & 0xf0) {
        case 0x00:
            sel = 0x38;
            break;
        case 0x10:
            sel = 0x39;
            break;
        case 0x20:
            sel = 0x10;
            break;
        default:
            sel = 2;
            break;
    }
    func_ov003_02217838(a, sel, (unsigned char) (arr[0] & 0xf), v1, v2, *(short *) (arr + 2), 6, b);
}
