/* func_ov143_02299880 @ 0x02299880, 0x5c bytes, Thumb, module ov143
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0xa0];
    unsigned char *array;
} UnkStruct_02299880;

extern int func_ov143_02299650(UnkStruct_02299880 *a, int n);
extern void func_ov143_022999a4(UnkStruct_02299880 *a, unsigned char byte, int c, int d);
extern void func_ov143_02299924(UnkStruct_02299880 *a, unsigned char byte, int c, int d);
extern int func_020896b8(int a, void *b, int c, int d, int e, int f, int g);
extern int data_ov143_0229af90;

void func_ov143_02299880(UnkStruct_02299880 *a, int b, int c, int d)
{
    if (func_ov143_02299650(a, 2) != 0) {
        func_ov143_022999a4(a, a->array[b], c, d);
    } else {
        func_ov143_02299924(a, a->array[b], c, d);
    }
    func_020896b8(1, &data_ov143_0229af90, c, d, -1, -1, 0);
}
