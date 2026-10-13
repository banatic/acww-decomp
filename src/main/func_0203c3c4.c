/* func_0203c3c4 @ 0x0203c3c4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_01ffcbb0(void *dst, const void *src);

void func_0203c3c4(const void *src, int *out1, int *out2)
{
    int stack[3];
    func_01ffcbb0(stack, src);
    *out1 = stack[0] >> 17;
    *out2 = stack[2] >> 17;
}
