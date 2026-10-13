/* func_0205d58c @ 0x0205d58c, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
    unsigned short arr[8];
} UnkStruct_0205d58c;
void func_0205d58c(UnkStruct_0205d58c *p, int i, unsigned short *v)
{
    p->arr[i] = *v;
}
