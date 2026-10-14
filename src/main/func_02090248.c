/* func_02090248 @ 0x02090248, 0x44 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e2724;
extern int data_020da13c;
extern void func_0209028c(void);
extern void __cxa_vec_cleanup(void *ptr, int a, int b, void (*fp)(void));
extern void func_020ee62c(void *ptr);
extern void func_020edf54(void *ptr);

void *func_02090248(void *p)
{
    *((int *) p) = (int) &data_020e2724;
    __cxa_vec_cleanup((char *) p + 0x35c, 4, 0x530, func_0209028c);
    *((int *) p) = (int) &data_020da13c;
    func_020ee62c(p);
    func_020edf54(p);
    return p;
}
