/* func_0208a144 @ 0x0208a144, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1e0(void *param1, int param2, int param3);

void func_0208a144(void *param0)
{
    int local;

    *(unsigned int *) ((char *) param0 + 0xc) = 0x1000;
    local = 0;
    func_0208a1e0(param0, local, 0);
}
