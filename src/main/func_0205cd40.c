/* func_0205cd40 @ 0x0205cd40, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x64];
    unsigned short arr[8];
} UnkStruct_0205cd40;
void func_0205cd40(UnkStruct_0205cd40 *p, int i, unsigned short v)
{
    p->arr[i] = v;
}
