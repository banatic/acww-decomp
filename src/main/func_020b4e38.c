/* func_020b4e38 @ 0x020b4e38, 0x1e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020b5074(void *p);
extern void func_020b50e0(void *p);

void func_020b4e38(unsigned char *p0)
{
    if (p0[0x46] != 0) {
        func_020b5074(p0);
    } else {
        func_020b50e0(p0);
    }
}
