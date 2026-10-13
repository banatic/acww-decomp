/* func_02013ee4 @ 0x02013ee4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160d4(unsigned int);
extern int func_02019e00(unsigned char *);
extern int func_02019de8(unsigned char *);
extern void func_0201462c(unsigned char *, unsigned char *);

void func_02013ee4(unsigned char *param0, unsigned char *param1)
{
    unsigned int r6;

    r6 = *(unsigned int *) (param1 + 0x634);
    if (r6 != 0) {
        if (func_020160d4(r6) != 0) {
            if (func_02019e00((unsigned char *) (func_020160d4(r6) + 0x564)) == 8) {
                if (func_02019de8((unsigned char *) (func_020160d4(r6) + 0x564)) == 0) {
                    return;
                }
            }
        }
    }
    if (func_02019e00(param1 + 0x564) != 8 || func_02019de8(param1 + 0x564) != 0) {
        func_0201462c(param0, param1);
        param0[0xa] = 1;
        param0[8] = 5;
    }
}
