/* func_02077880 @ 0x02077880, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_02077880;
extern void MI_CpuCopy8(void *dst, const void *src, int n);
void func_02077880(void *p, UnkStruct_02077880 v)
{
    MI_CpuCopy8(&v, p, 2);
}
