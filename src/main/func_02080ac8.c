/* func_02080ac8 @ 0x02080ac8, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0205195c(void *param1);
extern void func_020a8874(void *param1, void *param2, int param3);

void func_02080ac8(void *param1, void *param2)
{
    void *r4 = param1;
    void *r5 = param2;
    func_0205195c(r5);
    func_020a8874(r5, (char *) r4 + 0x7c6, 4);
}
