/* func_02097a74 @ 0x02097a74, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_021ef8ec[];
extern unsigned char *func_02098090(unsigned char *p, int a);
extern int func_02065ec0(unsigned char *p);
extern void func_02066830(unsigned char *p, int a);
extern void func_020664e0(unsigned char *p);

int func_02097a74(int a0, int a1, int a2)
{
    unsigned char *p;
    int i;

    p = func_02098090(&data_021ef8ec[a1 * 0xa04], 0);
    for (i = 0; i < 10; i++) {
        if (func_02065ec0(p) == 0) {
            func_02066830(p, a0);
            if (a2 != 0) {
                func_020664e0(p);
            }
            return 1;
        }
        p += 0x100;
    }
    return 0;
}
