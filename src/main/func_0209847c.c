/* func_0209847c @ 0x0209847c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

#define data_021dc7bc ((void *) 0x021dc7bc)
extern int func_020988d8(void *);
extern int func_02098844(void *, void *);
extern int func_02098530(void *);
extern int func_02098578(void);
extern int func_02098510(void *);

int func_0209847c(void *p)
{
    int r = 0;

    if (func_020988d8(p) == 1) {
        if (data_021dc7bc != 0) {
            r = func_02098844(data_021dc7bc, p);
        }
    } else if (func_02098530(p) == 1) {
        if (func_02098578() != 0) {
            r = func_02098578();
            r = r + 0x249c * func_02098510(p);
        }
    }
    return r;
}
