/* func_020a8210 @ 0x020a8210, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a8c38(void *param);
extern char data_020e3d64;

void *func_020a8210(void *param)
{
    *(void **) param = (void *) &data_020e3d64;
    func_020a8c38(param);
    return param;
}
