/* func_02065334 @ 0x02065334, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206531c(void *);
extern void func_02065284(void *);

void func_02065334(void *param)
{
    switch (*(int *) ((char *) param + 0x14)) {
        case 1:
            func_0206531c(param);
            break;
        case 2:
            func_02065284(param);
            break;
    }
}
