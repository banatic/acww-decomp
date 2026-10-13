/* func_0205f2b0 @ 0x0205f2b0, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x80];
    unsigned long arr[4];
} UnkStruct_0205f2b0;
unsigned long func_0205f2b0(UnkStruct_0205f2b0 *p, int i)
{
    return p->arr[i];
}
