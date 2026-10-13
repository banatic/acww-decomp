/* func_0205d598 @ 0x0205d598, 0xa bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
    unsigned short arr[8];
} UnkStruct_0205d598;
void func_0205d598(unsigned short *dst, UnkStruct_0205d598 *p, int i)
{
    *dst = p->arr[i];
}
