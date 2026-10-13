/* func_ov068_02272c30 @ 0x02272c30, 0x24 bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern int func_020912d4(int a, void *b, int c, int d);

typedef struct {
    char pad_00[0x2cc];
    char array[0x18];
    int result;
} UnkStruct_02272c30;

void func_ov068_02272c30(UnkStruct_02272c30 *obj)
{
    int zero = 0;
    obj->result = func_020912d4(0x42, obj->array, zero, zero);
}
