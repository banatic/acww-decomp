/* func_02011138 @ 0x02011138, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02011368(unsigned int arg);
extern unsigned short *func_020996e0(void *arg);

void func_02011138(unsigned short *dest, unsigned int src)
{
    *dest = *func_020996e0(func_02011368(src));
}
