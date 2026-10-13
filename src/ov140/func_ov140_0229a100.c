/* func_ov140_0229a100 @ 0x0229a100, 0x2c bytes, Thumb, module ov140
 * mwccarm 1.2/base -O4,s
 */

typedef struct UnkStructElem {
    char data[0x6c];
} UnkStructElem;

typedef struct UnkStruct_0229a100 {
    unsigned char pad_00[0x8e6];
    unsigned char flag;
    unsigned char pad_8E7[0x11d5];
    UnkStructElem array[3];
} UnkStruct_0229a100;

extern void func_02070b84(UnkStructElem *elem);

void func_ov140_0229a100(UnkStruct_0229a100 *obj)
{
    int i;
    obj->flag = 0;
    for (i = 0; i < 3; i++) {
        func_02070b84(&obj->array[i]);
    }
}
