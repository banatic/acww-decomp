/* func_020b8060 @ 0x020b8060, 0x270 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020b8060 {
    int x;
    int y;
    int z;
};
struct UnkStruct_020b8060_2 {
    char pad_00[0x44];
};

extern "C" void func_020ea6e0(UnkStruct_020b8060 *, int);
extern "C" int func_020b7fe0(UnkStruct_020b8060_2 *, UnkStruct_020b8060 *, UnkStruct_020b8060 *, UnkStruct_020b8060 *, int,
                             int);

extern "C" bool func_020b8060(UnkStruct_020b8060_2 *p, UnkStruct_020b8060 *q, int w, int h, int e, int f, int g, int i);

extern "C" bool func_020b8060(UnkStruct_020b8060_2 *p, UnkStruct_020b8060 *q, int w, int h, int e, int f, int g, int i)
{
    UnkStruct_020b8060 v[8];
    bool ok;

    v[0].x = v[4].x = v[1].x = v[5].x = -(w >> 1);
    v[2].x = v[6].x = v[3].x = v[7].x = w >> 1;
    v[0].z = v[4].z = v[3].z = v[7].z = -(h >> 1);
    v[1].z = v[5].z = v[2].z = v[6].z = h >> 1;
    if (f != 0) {
        func_020ea6e0(&v[0], f);
        func_020ea6e0(&v[1], f);
        func_020ea6e0(&v[2], f);
        func_020ea6e0(&v[3], f);
        v[4] = v[0];
        v[5] = v[1];
        v[6] = v[2];
        v[7] = v[3];
    }
    v[0].x += q->x;
    v[1].x += q->x;
    v[2].x += q->x;
    v[3].x += q->x;
    v[4].x += q->x;
    v[5].x += q->x;
    v[6].x += q->x;
    v[7].x += q->x;
    v[0].z += q->z;
    v[1].z += q->z;
    v[2].z += q->z;
    v[3].z += q->z;
    v[4].z += q->z;
    v[5].z += q->z;
    v[6].z += q->z;
    v[7].z += q->z;
    v[0].y = v[1].y = v[2].y = v[3].y = q->y;
    v[4].y = v[5].y = v[6].y = v[7].y = q->y + e;
    ok = true;
    ok |= func_020b7fe0(&p[0], &v[4], &v[5], &v[6], g, i);
    ok |= func_020b7fe0(&p[1], &v[4], &v[6], &v[7], g, i);
    ok |= func_020b7fe0(&p[2], &v[5], &v[1], &v[2], g, i);
    ok |= func_020b7fe0(&p[3], &v[5], &v[2], &v[6], g, i);
    ok |= func_020b7fe0(&p[4], &v[6], &v[2], &v[3], g, i);
    ok |= func_020b7fe0(&p[5], &v[6], &v[3], &v[7], g, i);
    ok |= func_020b7fe0(&p[6], &v[4], &v[0], &v[1], g, i);
    ok |= func_020b7fe0(&p[7], &v[4], &v[1], &v[5], g, i);
    ok |= func_020b7fe0(&p[8], &v[7], &v[3], &v[0], g, i);
    ok |= func_020b7fe0(&p[9], &v[7], &v[0], &v[4], g, i);
    return ok;
}
