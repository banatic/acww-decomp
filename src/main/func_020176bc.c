/* func_020176bc @ 0x020176bc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020164cc(void *p, int);
extern int func_02095a28(void);
extern void func_02016764(void *p1, void *p2, int a, unsigned short b, int c, int d, int e, int f);
extern unsigned short data_020c80f8;

void func_020176bc(char *param1, char *param2)
{
    int a;

    a = func_020164cc(param2 + 0x334, (int) param2);
    if (a != 0) {
        if (func_02095a28() != 0) {
            func_02016764(param2 + 0x334, param2, 0x23, data_020c80f8, 0, 0x1000, 0, 0);
            param1[0x98] = 1;
        }
    }
}
