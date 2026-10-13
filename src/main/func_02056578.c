/* func_02056578 @ 0x02056578, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02057054(void *arg);
extern unsigned int data_020dd154;

void *func_02056578(void *arg)
{
    *(unsigned int *) arg = (unsigned int) &data_020dd154;
    func_02057054(arg);
    return arg;
}
