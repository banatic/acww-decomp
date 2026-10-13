/* func_ov142_0229bbc4 @ 0x0229bbc4, 0x2e bytes, Thumb, module ov142
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *obj, int arg);
extern void func_ov142_0229b1b8(void *obj);
extern void func_ov002_022080a0(void *obj, int arg);
extern int func_ov002_02207f60(void *obj);

typedef struct {
    char pad_00[0x98];
    int value;
} UnkStruct_0229bbc4;

void func_ov142_0229bbc4(UnkStruct_0229bbc4 *obj)
{
    if (func_ov002_02207f48(obj, -1) != 0) {
        func_ov142_0229b1b8(obj);
        func_ov002_022080a0(obj, 2);
    }
    obj->value = func_ov002_02207f60(obj);
}
