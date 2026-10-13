/* func_02042ce8 @ 0x02042ce8, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02042f10(void *param1, int param2);
extern void func_02042f08(void *param1);

void func_02042ce8(void *param1)
{
    int i;
    void *ptr = param1;

    for (i = 0; i < 3; i++) {
        func_02042f10(ptr, i);
    }

    func_02042f08((void *) ((char *) ptr + 0x46c));
}
