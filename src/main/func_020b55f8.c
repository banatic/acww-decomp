/* func_020b55f8 @ 0x020b55f8, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020e5218;
extern void func_020a8c38(void *);
extern void func_020edb3c(void *);

void *func_020b55f8(void *param)
{
    ((unsigned int *) param)[0] = (unsigned int) &data_020e5218;
    func_020a8c38(param);
    func_020edb3c(param);
    return param;
}
