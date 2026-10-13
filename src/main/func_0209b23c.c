/* func_0209b23c @ 0x0209b23c, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209bd5c(void *param);

void func_0209b23c(void *param)
{
    unsigned char *ptr = (unsigned char *) param;
    func_0209bd5c(param);
    ptr[0xc] = 5;
    ptr[0xd] = 0;
}
