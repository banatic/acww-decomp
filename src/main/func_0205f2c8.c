/* func_0205f2c8 @ 0x0205f2c8, 0x16 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x48];
    int arr1[9];
    short arr2[1];
} UnkStruct_0205f2c8;

void func_0205f2c8(UnkStruct_0205f2c8 *s, int index, int val1, short val2)
{
    s->arr1[index] = val1;
    s->arr2[index] = val2;
}
