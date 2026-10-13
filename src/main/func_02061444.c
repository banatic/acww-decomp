/* func_02061444 @ 0x02061444, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020530b0(void *);
extern void func_02138c48(void *, int, int, void (*)(void));
extern void func_020614e4(void);

void *func_02061444(void *param)
{
    func_020530b0((char *) param + 0x400);
    func_02138c48(param, 2, 0x200, func_020614e4);
    return param;
}
