/* func_0206c2e4 @ 0x0206c2e4, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0206c2c4(void *, int);
extern void MI_CpuFill8(void *, int, int);

typedef struct {
    char pad_00[0x400];
    int used;
    int arr0[3];
    int unk_410;
    char pad_414[0x18];
    int arr1[3];
    char arr_b[3];
} UnkStruct_0206c2e4;

void func_0206c2e4(UnkStruct_0206c2e4 *obj, int v)
{
    unsigned int i;
    int val;
    obj->used = 0;
    MI_CpuFill8(obj, 0, 0x400);
    i = 0;
    val = i;
    goto test;
loop:
    obj->arr0[i] = val;
    obj->arr_b[i] = (char) val;
    obj->arr1[i] = val;
    i++;
test:
    if (i < 3) {
        goto loop;
    }
    obj->unk_410 = 0;
    func_0206c2c4(obj, v);
}
