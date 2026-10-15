/* func_020b9238 @ 0x020b9238, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e587c;
extern int data_020da13c;
extern void func_020ee62c(volatile unsigned int *p);

volatile unsigned int *func_020b9238(volatile unsigned int *p)
{
    unsigned int val;
    *p = (unsigned int) &data_020e587c;
    val = (unsigned int) &data_020da13c;
    *p = val;
    func_020ee62c(p);
    return p;
}
