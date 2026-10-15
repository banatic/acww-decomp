/* func_020675c0 @ 0x020675c0, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *);

void func_020675c0(void *param)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) param + 0x680))) != 0) {
        func_020a8fb8(condition_value0);
        *(unsigned int *) ((char *) param + 0x680) = 0;
    }
}
