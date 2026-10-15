/* func_0208b824 @ 0x0208b824, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8fb8(void *);

void func_0208b824(void *arg0)
{
    void *condition_value0;
    if ((condition_value0 = (void *) (*(unsigned int *) ((char *) arg0 + 0x38))) != 0) {
        func_020a8fb8(condition_value0);
        *(unsigned int *) ((char *) arg0 + 0x38) = 0;
    }
}
