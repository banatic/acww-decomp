/* func_02011d30 @ 0x02011d30, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c1284;
extern void func_02011d28(void *p);
extern int func_02011704(void *p, void *param2);
extern void func_020116bc(void *p);
extern void func_020116b4(void *param1);

void func_02011d30(void *param1, void *param2)
{
    void *p = &data_021c1284;

    func_02011d28(p);
    if (func_02011704(&data_021c1284, param2) != 0) {
        func_020116bc(p);
    }
    func_020116b4(param1);
}
