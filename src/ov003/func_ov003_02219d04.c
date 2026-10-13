/* func_ov003_02219d04 @ 0x02219d04, 0x88 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02096718(int);
extern void func_0204f794(void *, int, int);
extern int func_ov003_02219e14(void *, void *);

typedef struct {
    int x, y, z;
} Vec;
struct UnkStruct_02219d04 {
    char pad_00[0x2d8];
    int unk_2D8;
    char pad_2DC[0x7d4 - 0x2dc];
    unsigned char unk_7D4;
    unsigned char unk_7D5;
    char pad_7D6[0x7f0 - 0x7d6];
    int unk_7F0;
};

int func_ov003_02219d04(void *p0, int slot)
{
    Vec v;
    Vec v2;
    unsigned int h;
    int n;
    unsigned char *p;
    struct UnkStruct_02219d04 *o = (struct UnkStruct_02219d04 *) func_02096718(slot);
    if (o != 0) {
        h = (unsigned int) (o->unk_2D8 << 4) >> 16;
        n = 0;
        v.x = 0;
        v.y = 0;
        v.z = 0;
        if (o->unk_7F0 == 0x49) {
            p = &o->unk_7D4;
            func_0204f794(&v, *p, *(p + 1));
            n = 8 - h;
        } else if (o->unk_7F0 == 0x5d) {
            p = &o->unk_7D4;
            func_0204f794(&v, *p, *(p + 1));
            n = 5 - h;
        }
        if (n > 0) {
            v2.x = v.x;
            v2.y = v.y;
            v2.z = v.z;
            if (func_ov003_02219e14(p0, &v2) != 0) {
                return n;
            }
        }
    }
    return 0;
}
