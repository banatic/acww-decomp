/* func_ov140_0229a800 @ 0x0229a800, 0x5c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov140_0229a164(unsigned char *, int);
extern int func_0206fe60(void);
extern void func_ov140_0229a7e8(void *);
extern void func_ov002_02208098(void *, int);
extern void func_ov140_0229a544(void *);
extern void func_ov140_02299f90(void *, int);

void func_ov140_0229a800(unsigned char *p)
{
    if (p[0x8db] < 5) {
        func_ov140_0229a164(p, p[0x8db]);
        p[0x8db]++;
    } else {
        func_ov140_0229a164(p, 5);
        *(int *) (p + 0xa8) = 8;
        if (func_0206fe60()) {
            func_ov140_0229a7e8(p);
        } else {
            func_ov002_02208098(p, 1);
            func_ov140_0229a544(p);
        }
        func_ov140_02299f90(p, 0x20);
    }
}
