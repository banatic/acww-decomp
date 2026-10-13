/* func_020666e4 @ 0x020666e4, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02003790(void *param1, void *param2);

void func_020666e4(void *param1, void *param2)
{
    unsigned char *ptr = (unsigned char *) param1;
    ptr[0x1e] = 3;
    func_02003790(param2, param1);
}
