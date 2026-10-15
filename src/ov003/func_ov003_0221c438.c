/* func_ov003_0221c438 @ 0x0221c438, 0x58 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern int func_0203cff8(void *, int);
extern int func_0203cfc8(void *);
extern int func_020b9d3c(void *, int, int *, int, int, int);
extern int func_020b374c(int *);
extern void func_020b3850(int, int);
extern int data_ov003_02238a70;
extern int data_021f34b0;

typedef struct {
    char pad_00[0x28];
    int unk_28;
} UnkStruct_0221c438;

int func_ov003_0221c438(UnkStruct_0221c438 *a, int b, int c)
{
    if (func_0203cff8(&a->unk_28, c) != 0) {
        int tmp = func_0203cfc8(&a->unk_28);
        if (func_020b9d3c(a, b, &data_ov003_02238a70, tmp, 0, 0) != 0) {
            func_020b3850(func_020b374c(&data_021f34b0), c);
            return 1;
        }
    }
    return 0;
}
