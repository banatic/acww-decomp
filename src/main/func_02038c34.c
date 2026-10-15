/* func_02038c34 @ 0x02038c34, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da548;
extern void *func_020a8c38(void *);
extern void func_020edb3c(void *);

void *func_02038c34(void *param)
{
    *(void **) param = &data_020da548;
    func_020a8c38(param);
    func_020edb3c(param);
    return param;
}
