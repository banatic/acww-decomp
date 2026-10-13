/* func_ov051_02260ea0 @ 0x02260ea0, 0x20 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206844c(void *param1, void *param2, int param3);

extern int data_ov051_022615c0;

void func_ov051_02260ea0(void *param0)
{
    unsigned char local;
    void *ptr;

    local = 2;
    ptr = &local;
    func_0206844c(*(void **) ((char *) param0 + 0x40), ptr, data_ov051_022615c0);
}
