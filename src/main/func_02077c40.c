/* func_02077c40 @ 0x02077c40, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

void func_02077c40(void *param)
{
    extern void func_02077e68(void *);
    extern void func_02051bf8(void *, int);

    func_02077e68(param);
    func_02051bf8((char *) param + 0xc, 6);
    func_02051bf8((char *) param + 0x18, 6);
}
