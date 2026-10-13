/* func_ov046_02260474 @ 0x02260474, 0x34 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov046_022604a8(void *);
extern void func_ov046_02261268(void *, int);
extern void func_0203ac04(void);
extern void func_0203e0a8(void *, int);

int func_ov046_02260474(void *r0)
{
    void *r4 = r0;
    if (func_ov046_022604a8(r4) != 0) {
        func_ov046_02261268((char *) r4 + 0x658, 4);
        func_0203ac04();
        func_0203e0a8(r4, 0);
        return 1;
    }
    return 0;
}
