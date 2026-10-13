/* func_02096df4 @ 0x02096df4, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02097f14(void *p);
extern int func_02065ec0(void);
extern int func_02096de0(void);
extern int func_02065f88(int a, int b, void *c);
extern char data_021f36ec;
extern char data_020e3070;

int func_02096df4(int param)
{
    int temp = func_02097f14(&data_021f36ec);
    if (func_02065ec0() != 0) {
        return 0;
    }
    if (func_02096de0() == 0) {
        return 0;
    }
    func_02065f88(temp, param, &data_020e3070);
    return 1;
}
