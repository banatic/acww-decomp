/* func_0204f794 @ 0x0204f794, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} UnkStruct_0204f794;

void func_0204f794(UnkStruct_0204f794 *p, unsigned int a, unsigned int b)
{
    p->x = (a << 13) + 0x1000;
    p->z = (b << 13) + 0x1000;
    p->y = 0;
}
