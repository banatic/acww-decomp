/* func_ov003_02235ce8 @ 0x02235ce8, 0x70 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int x, y, z;
    unsigned char c, d;
    unsigned char pad_0E[2];
} UnkStruct_02235ce8;
extern UnkStruct_02235ce8 data_ov003_02262aa8[];
extern void *data_020ccf94;
extern int func_020a7278(void *a);
extern int func_02073d90(void *a);
extern void func_020771cc(int a, void *b, int c, int d);

int func_ov003_02235ce8(void *a, int i, int c, const int *v, unsigned char e, void *f)
{
    // Both guards nest onto the single trailing return 0.
    if (func_020a7278(a) != 0) {
        if (func_02073d90(data_020ccf94) != 0) {
            func_020771cc(i + 0x18, &f, 0, 0);
            data_ov003_02262aa8[i].c = (unsigned char) c;
            data_ov003_02262aa8[i].x = v[0];
            data_ov003_02262aa8[i].y = v[1];
            data_ov003_02262aa8[i].z = v[2];
            data_ov003_02262aa8[i].d = e;
            return 1;
        }
    }
    return 0;
}
