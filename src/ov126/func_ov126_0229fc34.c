/* func_ov126_0229fc34 @ 0x0229fc34, 0x20 bytes, Thumb, module ov126
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov126_0229fc54(int *obj);
extern int func_02077c34(int arg);
extern int func_02051c08(int a, void *b, int c);

void func_ov126_0229fc34(int *obj)
{
    int a;
    int b;
    a = func_ov126_0229fc54(obj);
    b = func_02077c34(a);
    func_02051c08(b, (void *) ((char *) obj + 0x4248), 6);
}
