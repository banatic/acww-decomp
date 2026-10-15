/* func_02060b70 @ 0x02060b70, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65c4(void);
extern void *func_02060b84(int);

void *func_02060b70(void)
{
    return func_02060b84((int) func_020b65c4());
}
