/* func_ov002_0220b0f4 @ 0x0220b0f4, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bdac;
extern void func_0208ad24(void *);

void *func_ov002_0220b0f4(void *arg)
{
    *((void **) arg) = &data_ov002_0220bdac;
    func_0208ad24(arg);
    return arg;
}
