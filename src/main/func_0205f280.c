/* func_0205f280 @ 0x0205f280, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned long arr[4];
} UnkStruct_0205f280;
unsigned long func_0205f280(UnkStruct_0205f280 *p, int i)
{
    return p->arr[i];
}
