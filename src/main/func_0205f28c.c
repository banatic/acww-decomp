/* func_0205f28c @ 0x0205f28c, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa4];
    unsigned short arr[4];
} UnkStruct_0205f28c;
unsigned short func_0205f28c(UnkStruct_0205f28c *p, int i)
{
    return p->arr[i];
}
