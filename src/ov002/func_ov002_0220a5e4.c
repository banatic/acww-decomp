/* func_ov002_0220a5e4 @ 0x0220a5e4, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bcec;
extern void *func_0208ebb8(void *);

void *func_ov002_0220a5e4(void *arg)
{
    *((void **) arg) = &data_ov002_0220bcec;
    func_0208ebb8(arg);
    return arg;
}
