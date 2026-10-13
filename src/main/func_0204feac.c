/* func_0204feac @ 0x0204feac, 0x24 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int a;
    int b;
    int c;
} UnkStruct_0204feac;
extern UnkStruct_0204feac data_020dce14[];
extern UnkStruct_0204feac data_020dce18[];

int func_0204feac(int *out0, int *out1, unsigned int index)
{
    if (index >= 4) {
        return 0;
    }
    *out0 = data_020dce14[index].a;
    *out1 = data_020dce18[index].a;
    return 1;
}
