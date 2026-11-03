/* scene_motion_kinds_5: 2 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02018ff4 @ 0x02018ff4, 0x3c bytes, Thumb
 * func_02018fdc @ 0x02018fdc, 0x18 bytes, Thumb
 */

typedef struct {
    char data[28];
} UnkStruct_02018fdc;

extern int func_02019de8(unsigned char *p);
extern int func_020164cc(unsigned char *p, unsigned char *q);
extern void func_02019af0(unsigned char *p, int v);
extern UnkStruct_02018fdc data_020c8290[];

void func_02018ff4(unsigned char *p, unsigned char *q)
{
    if (p[0x98] < 1) {
        return;
    }
    if (func_02019de8(p) != 0) {
        return;
    }
    if (func_020164cc(q + 0x334, q) == 0) {
        return;
    }
    func_02019af0(p, 1);
}

UnkStruct_02018fdc *func_02018fdc(unsigned int idx)
{
    if (idx < 60) {
        return &data_020c8290[idx];
    }
    return 0;
}
