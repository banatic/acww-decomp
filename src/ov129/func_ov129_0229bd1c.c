/* func_ov129_0229bd1c @ 0x0229bd1c, 0x30 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2f78];
    unsigned short arr[16];
} UnkStruct_0229bd1c;

int func_ov129_0229bd1c(UnkStruct_0229bd1c *p)
{
    int i;
    for (i = 0; i < 16; i++) {
        if (p->arr[i] == 0xffff) {
            return i;
        }
    }
    return -1;
}
