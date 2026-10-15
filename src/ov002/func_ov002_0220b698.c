/* func_ov002_0220b698 @ 0x0220b698, 0x18 bytes, Thumb, module ov002
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0208f58c(void *arg, char parameter1, int parameter2);
extern int data_ov002_0220bd90;

void *func_ov002_0220b698(void *arg, char arg1, int arg2)
{
    func_0208f58c(arg, arg1, arg2);
    *(void **) arg = &data_ov002_0220bd90;
    return arg;
}
