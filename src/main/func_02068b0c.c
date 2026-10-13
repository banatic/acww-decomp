/* func_02068b0c @ 0x02068b0c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020def3c;
extern void func_020edb3c(unsigned int *p);

unsigned int *func_02068b0c(unsigned int *p)
{
    *p = (unsigned int) &data_020def3c;
    func_020edb3c(p);
    return p;
}
