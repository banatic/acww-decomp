/* func_ov047_02262594 @ 0x02262594, 0x34 bytes, Thumb, module ov047
 * mwccarm 1.2/base -O4,s
 */

extern int func_0202ec14(void *);
extern void func_0209129c(unsigned int);

int func_ov047_02262594(void *param)
{
    if (func_0202ec14(param) == 0) {
        return 0;
    }
    if (*(unsigned int *) ((char *) param + 0x73c) != -1) {
        func_0209129c(*(unsigned int *) ((char *) param + 0x73c));
        *(unsigned int *) ((char *) param + 0x73c) = -1;
    }
    return 1;
}
