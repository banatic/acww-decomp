/* func_0205f274 @ 0x0205f274, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xb8];
    unsigned long arr[4];
} UnkStruct_0205f274;
void func_0205f274(UnkStruct_0205f274 *p, int i, unsigned long v)
{
    p->arr[i] = v;
}
