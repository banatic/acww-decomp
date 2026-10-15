/* func_02053ed8 @ 0x02053ed8, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206e71c(void *ptr);
extern int func_0206e8b4(void *ptr);

void *func_02053ed8(void *param)
{
    func_0206e71c(param);
    func_0206e8b4((char *) param + 0x38);
    func_0206e8b4((char *) param + 0x1c);
    func_0206e8b4(param);
    return param;
}
