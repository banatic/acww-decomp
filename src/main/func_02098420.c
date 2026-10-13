/* func_02098420 @ 0x02098420, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020988d8(void *);
extern int func_020988a4(void *, void *);
extern int func_02098530(void *);
extern int func_02098578(void);
extern int func_02098510(void *);
extern int func_02099a28(int);

extern unsigned char data_021dc7bc[];

int func_02098420(void *arg0)
{
    int result = 0;
    if (func_020988d8(arg0) == 1) {
        if ((void *) data_021dc7bc != 0) {
            result = func_020988a4((void *) data_021dc7bc, arg0);
        }
    } else {
        if (func_02098530(arg0) == 1) {
            if (func_02098578() != 0) {
                int x = func_02098510(arg0);
                int y = func_02098578();
                result = func_02099a28(y + x * 0x249c);
            }
        }
    }
    return result;
}
