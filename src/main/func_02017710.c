/* func_02017710 @ 0x02017710, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02057bd4(void);
extern int func_02057d0c(int, int);
extern int func_02016764(int, int, int, int, int, int, int, int);
extern int func_020164a0(int, int);
extern void func_02054768(int, int, int);
extern void func_02057b90(int, int);
extern void func_02019af0(int, int);
extern unsigned short data_020c80f8;

int func_02017710(int r0, int r1)
{
    int r5 = r0;
    int r4 = r1;
    int sp[5];
    int r0_2;
    int r0_3;
    int r0_4;

    if (func_02057bd4() != 0) {
        if (func_02057d0c(7, r4) != 0) {
            sp[0] = 3;
            sp[1] = 0x1000;
            sp[2] = 0;
            sp[3] = 0;
            r0_2 = func_02016764(r4 + 0x334, r4, 0x26, data_020c80f8, sp[0], sp[1], sp[2], sp[3]);
            r0_3 = func_020164a0(r4 + 0x334, 1);
            if (r0_3 == 0x139) {
                func_02054768(r4 + 0xec, 0, 0);
            }
            func_02057b90(5, r4);
            func_02019af0(r5, 0);
        }
    }
    return 1;
}
