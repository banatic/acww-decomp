/* func_0205ccf0 @ 0x0205ccf0, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x96];
    unsigned short arr[8];
} UnkStruct_0205ccf0;
void func_0205ccf0(UnkStruct_0205ccf0 *p, int i, unsigned short v)
{
    p->arr[i] = v;
}
