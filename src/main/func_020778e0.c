/* func_020778e0 @ 0x020778e0, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_020778e0;
extern void MI_CpuCopy8(void *dst, const void *src, int n);
void func_020778e0(void *p, UnkStruct_020778e0 v)
{
    MI_CpuCopy8(&v, p, 2);
}
