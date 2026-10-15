/* func_0206fc1c @ 0x0206fc1c, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021cfd28;
extern void func_02051bf8(void *a, int b);
extern int func_02051c08(void *a, void *b, int c);

int func_0206fc1c(void *param1, int param2)
{
    func_02051bf8(&data_021cfd28, 0x10);
    return func_02051c08(param1, &data_021cfd28, param2);
}
