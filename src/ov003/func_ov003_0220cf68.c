/* func_ov003_0220cf68 @ 0x0220cf68, 0xd8 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0204f818(int *a, int *b, int c);
extern int func_ov003_0220c934(int a);
extern int func_0200fdd0(int a, int *b, int c, int d);

int func_ov003_0220cf68(int a, int b, unsigned char *c)
{
    int x;
    int y;
    int t[2];

    func_0204f818(&x, &y, b);
    if (*c) {
        if (func_ov003_0220c934(a)) {
            return 2;
        }
        t[0] = 0;
        t[1] = 0;
        t[0] = x;
        t[1] = y;
        switch (func_0200fdd0(a, t, 2, 3)) {
            case 0:
                return 7;
            case 1:
                return 0;
            case 2:
                return 2;
        }
    }
    if (*(int *) ((char *) a + 0x818) == 2) {
        return 7;
    }
    if (*(int *) ((char *) a + 0x818) == 0) {
        return 0;
    }
    switch (*(int *) ((char *) a + 0x814)) {
        case 23:
            return 1;
        case 12:
        case 13:
            return 2;
        case 14:
            return 8;
        case 19:
        case 20:
            return 6;
        case 9:
        case 21:
            return 5;
        case 10:
        case 22:
            return 9;
        case 11:
            return 4;
        case 8:
        default:
            return 3;
    }
}
