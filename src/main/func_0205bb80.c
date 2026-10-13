/* func_0205bb80 @ 0x0205bb80, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02060ee0(void *, int);
extern void *func_02061204(void *, int);
extern int data_021ebcd4;

void func_0205bb80(unsigned short *dst, int unused, int param)
{
    *dst = *(unsigned short *) func_02061204(func_02060ee0(&data_021ebcd4, param), 0);
}
