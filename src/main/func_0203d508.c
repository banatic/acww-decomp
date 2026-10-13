/* func_0203d508 @ 0x0203d508, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020da97c;
extern void func_020a8188(void *);
extern void func_020edb3c(void *);

void *func_0203d508(void *param)
{
    *(void **) param = (void *) &data_020da97c;
    func_020a8188(param);
    func_020edb3c(param);
    return param;
}
