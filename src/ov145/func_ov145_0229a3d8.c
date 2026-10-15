/* func_ov145_0229a3d8 @ 0x0229a3d8, 0x24 bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208e484(void *);
extern void func_ov145_02299e44(void *);
extern unsigned char *func_ov002_02208098(void *object, unsigned char value);

void func_ov145_0229a3d8(void *p)
{
    if (func_0208e484((char *) p + 0xc8) != 0) {
        func_ov145_02299e44(p);
        func_ov002_02208098((void *) (p), *(unsigned char *) ((char *) p + 0xc3));
    }
}
