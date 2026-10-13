/* func_020910e4 @ 0x020910e4, 0x26 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02091140(void *p);
extern void MI_CpuCopy8(void *p, int result, void *field);

int func_020910e4(void *unused, void *ptr)
{
    void *field;
    int result;

    field = *(void **) ((char *) ptr + 0x18);
    result = func_02091140(field);
    if (result != 0) {
        ptr = (char *) ptr + 0x20;
        MI_CpuCopy8(ptr, result, field);
    }
    return result;
}
