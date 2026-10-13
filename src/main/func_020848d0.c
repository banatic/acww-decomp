/* func_020848d0 @ 0x020848d0, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x;
    int y;
    int z;
} Vec3i;

typedef struct {
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
} UnkStruct_020848d0;

extern void *data_021c80bc;
extern int func_0204f490(void *g, int *a, int *b, int *c, int *d, unsigned short *e1, unsigned short *e2, int n, int zero);
extern void func_0204f778(Vec3i *pos, int a, int b, int c, int d);

int func_020848d0(int unused, Vec3i *pos, UnkStruct_020848d0 *out)
{
    void *g = data_021c80bc;
    int a = 0, b = 0, c = 0, d = 0;
    unsigned short e1, e2;

    if (g != 0) {
        e1 = 0x5014;
        e2 = 0x501a;
        if (func_0204f490(g, &a, &b, &c, &d, &e1, &e2, 1, 0) != 0) {
            out->unk_00 = 0;
            out->unk_02 = 0x4000;
            out->unk_04 = 0;
            func_0204f778(pos, a, b, c, d);
            pos->x -= 0x8000;
            pos->z += 0x6000;
            pos->y = 0;
            return 1;
        }
    }
    return 0;
}
