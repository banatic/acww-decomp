/* func_020a9190 @ 0x020a9190, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8eac(void *);

void func_020a9190(void *arg)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg + 0x24))) != 0) {
        func_020a8eac(condition_value0);
    }
}
