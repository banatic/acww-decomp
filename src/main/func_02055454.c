/* func_02055454 @ 0x02055454, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02055f1c(void *);

int func_02055454(int param)
{
    int r4;
    int r5;
    int result;

    r5 = param;
    r4 = 1;
    result = func_02055f1c((void *) param);
    r4 &= result;
    *(unsigned int *) (r5 + 0x98) = 0x4e554c4c;
    return r4;
}
