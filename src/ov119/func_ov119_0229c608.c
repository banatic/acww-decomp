/* func_ov119_0229c608 @ 0x0229c608, 0x3e bytes, Thumb, module ov119
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x8c];
    unsigned char unk_8C;
} UnkStruct_0229c608;

extern int func_020ee45c(UnkStruct_0229c608 *obj, int index);
extern void func_ov090_022993cc(int a, unsigned char b);
extern void func_ov002_022080a0(UnkStruct_0229c608 *obj, int c);

int func_ov119_0229c608(UnkStruct_0229c608 *obj, int index)
{
    int ret = func_020ee45c(obj, index);
    if (index != -1 && index != 6) {
        func_ov090_022993cc(ret, (unsigned char) index);
        obj->unk_8C = 3;
        func_ov002_022080a0(obj, 1);
        return 1;
    } else {
        return 0;
    }
}
