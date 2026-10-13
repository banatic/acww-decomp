/* func_0201cb68 @ 0x0201cb68, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164a0(int, int);
extern int data_020c8ed4[];
extern int data_020c8ee8[];

int func_0201cb68(int unused, int param)
{
    int x = func_020164a0(param + 0x334, 0);
    int *p1 = data_020c8ed4;
    int *p2 = data_020c8ee8;
    int i;
    for (i = 0; i < 5; i++) {
        if (x == *p1 || x == *p2) {
            return 1;
        }
        p1++;
        p2++;
    }
    return 0;
}
