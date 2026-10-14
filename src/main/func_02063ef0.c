/* func_02063ef0 @ 0x02063ef0, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void __cxa_vec_ctor(void *, int, int, void *, void *);

extern void func_0206411c(void);
extern void func_02064120(void);

void *func_02063ef0(void *param)
{
    __cxa_vec_ctor(param, 9, 1, (void *) func_02064120, (void *) func_0206411c);
    return param;
}
