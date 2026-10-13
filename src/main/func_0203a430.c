/* func_0203a430 @ 0x0203a430, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020da6dc;
extern void func_020edb3c(void *ptr);

void *func_0203a430(void *arg)
{
    *(unsigned int *) arg = (unsigned int) &data_020da6dc;
    func_020edb3c(arg);
    return arg;
}
