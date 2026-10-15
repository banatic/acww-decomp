/* func_0203efdc @ 0x0203efdc, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02003518(void *object);
extern int func_020e8ce0(void *p, void *q);
extern int data_021c72cc;

int func_0203efdc(char *param)
{
    if (func_02003518(param) == 0) {
        return 0;
    }
    param += 0xd4;
    func_020e8ce0(&data_021c72cc, param);
    return 1;
}
