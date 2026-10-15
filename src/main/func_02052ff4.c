/* func_02052ff4 @ 0x02052ff4, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02052f3c(int);
extern void func_02053088(void *);

int func_02052ff4(int argument0)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (func_02052f3c((int) argument0))) != 0) {
        func_02053088(condition_value0);
        return 1;
    }
    return 0;
}
