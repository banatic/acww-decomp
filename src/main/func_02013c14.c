/* func_02013c14 @ 0x02013c14, 0x12 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02013c04(void);

void func_02013c14(void *param)
{
    func_02013c04();
    *(unsigned int *) ((char *) param + 4) = 5;
}
