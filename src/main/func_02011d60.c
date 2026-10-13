/* func_02011d60 @ 0x02011d60, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021c1284;
extern void func_02011d28(void *);
extern int func_020117f8(void *, void *);
extern void func_020117a8(void *);
extern void func_020117a0(void *);

void func_02011d60(void *param1, void *param2)
{
    void *ptr = &data_021c1284;
    func_02011d28(ptr);
    if (func_020117f8(&data_021c1284, param2)) {
        func_020117a8(ptr);
    }
    func_020117a0(param1);
}
