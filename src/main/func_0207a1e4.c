/* func_0207a1e4 @ 0x0207a1e4, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    signed char b[4];
} UnkStruct_0207a1e4;
extern int func_0207a210(UnkStruct_0207a1e4 *p);
void func_0207a1e4(UnkStruct_0207a1e4 *p)
{
    int i = func_0207a210(p);
    if ((unsigned int) i < 4) {
        for (; i < 3; i = i + 1) {
            p->b[i] = p->b[i + 1];
        }
        p->b[3] = -1;
    }
}
