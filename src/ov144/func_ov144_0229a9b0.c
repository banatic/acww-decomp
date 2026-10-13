/* func_ov144_0229a9b0 @ 0x0229a9b0, 0x24 bytes, Thumb, module ov144
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov144_0229a0e0(void *);
extern void func_ov002_02208098(void *, unsigned char);

void func_ov144_0229a9b0(void *arg0)
{
    if (func_0208e484((char *) arg0 + 0xc4)) {
        func_ov144_0229a0e0(arg0);
        func_ov002_02208098(arg0, *(unsigned char *) ((char *) arg0 + 0xbe));
    }
}
