/* func_ov002_0220b464 @ 0x0220b464, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern int data_ov002_0220bd74;
extern void *func_ov002_0220b648(void *);

void *func_ov002_0220b464(void *arg)
{
    *((void **) arg) = &data_ov002_0220bd74;
    func_ov002_0220b648(arg);
    return arg;
}
