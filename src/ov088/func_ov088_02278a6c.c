/* func_ov088_02278a6c @ 0x02278a6c, 0x20 bytes, Thumb, module ov088
 * mwccarm 1.2/base -O4,s
 */

extern int func_02013a14(void *p);

int func_ov088_02278a6c(void *arg)
{
    int flag = ((unsigned char *) arg)[0x739];
    if (flag) {
        return func_02013a14(arg);
    } else {
        return -1;
    }
}
