/* func_0206a978 @ 0x0206a978, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a873c(void *param1, void *param2);
extern void func_020676c4(void *param1, unsigned char param2);

void func_0206a978(void *param0)
{
    unsigned char local;
    void *ptr;

    ptr = param0;
    func_020a873c((void *) ((unsigned int) ptr + 0x38), &local);
    func_020676c4(*(void **) ((unsigned int) ptr + 0x24), local);
}
