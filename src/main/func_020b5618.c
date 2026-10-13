/* func_020b5618 @ 0x020b5618, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e5218;
extern void func_020a8c38(void *);

void *func_020b5618(void *param)
{
    *(void **) param = &data_020e5218;
    func_020a8c38(param);
    return param;
}
