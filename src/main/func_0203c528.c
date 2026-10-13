/* func_0203c528 @ 0x0203c528, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203c528(void *param);

int func_0203c528(void *param)
{
    int result;
    int *ptr1;
    int *ptr2;

    ptr1 = (int *) ((char *) param + 0xb8);
    ptr2 = (int *) ((char *) param + 0xa8);
    result = *ptr1 + *ptr2;
    if (result < 0) {
        result = 0;
    }
    return result;
}
