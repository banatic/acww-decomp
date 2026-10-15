/* func_02094f64 @ 0x02094f64, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020a887c(void *);
extern int data_020e2f54;

void *func_02094f64(void *arg)
{
    *(unsigned int *) arg = (unsigned int) &data_020e2f54;
    func_020a887c(arg);
    return arg;
}
