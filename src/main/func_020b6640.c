/* func_020b6640 @ 0x020b6640, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned char func_020b65c4(void);
extern int func_020b6654(int);

int func_020b6640(void)
{
    return func_020b6654((int) func_020b65c4());
}
