/* func_0203931c @ 0x0203931c, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[0xB8];
} UnkStruct_0203931c;

extern void func_02039e44(UnkStruct_0203931c *p);

typedef struct {
    char pad_00[4];
    UnkStruct_0203931c elements[4];
    int array1[4];
    int array2[4];
} Object;

void func_0203931c(Object *obj)
{
    int i;
    for (i = 0; i < 4; i++) {
        func_02039e44(&obj->elements[i]);
        obj->array1[i] = 0;
        obj->array2[i] = 0;
    }
}
