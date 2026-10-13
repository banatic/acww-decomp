/* func_0203aa24 @ 0x0203aa24, 0x22 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f844(void *buffer, int arg2);
extern void func_0203aa48(int arg0, int arg1, void *buffer);

void func_0203aa24(int arg0, int arg1, int arg2)
{
    char buffer[12];

    func_0203f844(buffer, arg2);
    func_0203aa48(arg0, arg1, buffer);
}
