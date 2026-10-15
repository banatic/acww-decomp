/* func_0208a4dc @ 0x0208a4dc, 0x32 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *);

void func_0208a4dc(void *arg0)
{
    void *condition_value0;
    void *condition_value1;
    if ((condition_value0 = (void *) (*(int *) ((char *) arg0 + 0xc0))) != 0) {
        func_020a8fb8(condition_value0);
        *(int *) ((char *) arg0 + 0xc0) = 0;
    }
    if ((condition_value1 = (void *) (*(int *) ((char *) arg0 + 0xc4))) != 0) {
        func_020a8fb8(condition_value1);
        *(int *) ((char *) arg0 + 0xc4) = 0;
    }
}
