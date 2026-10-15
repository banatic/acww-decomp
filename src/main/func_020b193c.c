/* func_020b193c @ 0x020b193c, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_020e4290;
extern void *func_020a8c38(void *);

void *func_020b193c(void *param)
{
    *(void **) param = &data_020e4290;
    func_020a8c38(param);
    return param;
}
