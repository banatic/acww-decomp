/* func_020b54c8 @ 0x020b54c8, 0x1c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a9a90(void *p, int arg);
extern int data_020e51e8;

void *func_020b54c8(void *param)
{
    func_020a9a90(param, 0);
    *(void **) param = &data_020e51e8;
    return param;
}
