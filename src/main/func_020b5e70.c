/* func_020b5e70 @ 0x020b5e70, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020b5e10(void);
extern int func_020b5e84(unsigned char *);

int func_020b5e70(void)
{
    return func_020b5e84((unsigned char *) func_020b5e10());
}
