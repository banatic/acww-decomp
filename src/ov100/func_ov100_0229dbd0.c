/* func_ov100_0229dbd0 @ 0x0229dbd0, 0x28 bytes, Thumb, module ov100
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov100_0229ca7c(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov100_0229dbd0(void *r0)
{
    if (func_0208e484((char *) r0 + 0x2274)) {
        func_ov100_0229ca7c(r0);
        func_ov002_02208098((void *) (r0), 4);
    }
}
