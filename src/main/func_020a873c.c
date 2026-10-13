/* func_020a873c @ 0x020a873c, 0x14 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a87c8(void *param, int param2);

typedef struct {
    unsigned char pad_00[0xc];
    void *ptr;
} UnkStruct020a873c;

void func_020a873c(UnkStruct020a873c *a, unsigned char *out)
{
    *out = (unsigned char) func_020a87c8(a->ptr, 0);
}
