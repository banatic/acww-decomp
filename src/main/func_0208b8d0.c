/* func_0208b8d0 @ 0x0208b8d0, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *ptr, void *arg);
extern void func_0208a1ec(void *ptr, int arg);
extern void *func_0208a144(void *ptr);
extern char data_020d5c5c;

void func_0208b8d0(char *param)
{
    *(int *) (param + 0x20) = 3;
    func_0208a1f0(param + 0xc, &data_020d5c5c);
    func_0208a1ec(param + 0xc, 1);
    func_0208a144(param + 0xc);
}
