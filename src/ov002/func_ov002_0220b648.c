/* func_ov002_0220b648 @ 0x0220b648, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bd90;
extern void *func_0208f46c(void *);

void *func_ov002_0220b648(void *arg)
{
    *((void **) arg) = &data_ov002_0220bd90;
    func_0208f46c(arg);
    return arg;
}
