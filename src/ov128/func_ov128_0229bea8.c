/* func_ov128_0229bea8 @ 0x0229bea8, 0x34 bytes, Thumb, module ov128
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern int func_ov128_0229b7ec(void *, int);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);
extern void func_ov128_0229bbe4(void *);

void func_ov128_0229bea8(void *r0)
{
    if (func_0208e484((char *) r0 + 0x110)) {
        if (func_ov128_0229b7ec(r0, 2)) {
            func_ov002_02208098((void *) (r0), 3);
            func_ov128_0229bbe4(r0);
        }
    }
}
