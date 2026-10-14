/* func_02035494 @ 0x02035494, 0x7c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02035a18(void *);
extern void func_02035b14(void *);
extern void func_02035f44(void *);
extern void func_02035ff4(void *);
extern void func_02036864(void *);
extern void func_020369d0(void *);
extern void func_02037450(void *);
extern void func_02036510(void *);
extern void __cxa_vec_cleanup(void *, int, int, void (*)(void));
extern void func_020374cc(void);

void *func_02035494(void *param)
{
    func_02035a18((char *) param + 0x2F0);
    func_02035b14((char *) param + 0x2E4);
    func_02035f44((char *) param + 0x2D0);
    func_02035ff4((char *) param + 0x2B4);
    func_02036864((char *) param + 0x2A0);
    func_020369d0((char *) param + 0x264);
    func_02037450((char *) param + 0x24C);
    func_02036510((char *) param + 0x1C4);
    __cxa_vec_cleanup(param, 0x10, 0x1C, func_020374cc);
    return param;
}
