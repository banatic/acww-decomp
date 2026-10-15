/* func_0203a38c @ 0x0203a38c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *arg);
extern char data_020da628;

void *func_0203a38c(void *arg)
{
    *((void **) arg) = &data_020da628;
    func_020a887c(arg);
    return arg;
}
