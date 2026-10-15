/* func_02010004 @ 0x02010004, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char data_020e54a8;
extern int func_ov004_02225fb8(void *self, int action);
extern int func_ov003_0220c328(void *self, void *arg1, ...);

int func_02010004(int a, int b)
{
    unsigned int flag;
    flag = (data_020e54a8 == 1) ? 1 : 0;
    if (flag != 0) {
        asm { mov r2, #0 }
        return func_ov004_02225fb8((void *) a, b);
    } else {
        return func_ov003_0220c328((void *) a, (void *) b);
    }
}
