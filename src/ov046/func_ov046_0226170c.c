/* func_ov046_0226170c @ 0x0226170c, 0x44 bytes, Thumb, module ov046
 * mwccarm 1.2/base -O4,s
 */

extern int func_02014868(void *p);
extern void func_ov046_02261268(void *p, int n);
extern int func_0203e020(void *p);
extern void func_ov046_022619cc(void *p, int n);

int func_ov046_0226170c(char *obj)
{
    if (func_02014868(obj + 0x618) == 0) {
        obj[0x73e] = 0;
        func_ov046_02261268(obj + 0x658, 5);
        func_0203e020(obj);
        func_ov046_022619cc(obj, 4);
    }
    return 1;
}
