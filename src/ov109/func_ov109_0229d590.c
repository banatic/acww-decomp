/* func_ov109_0229d590 @ 0x0229d590, 0x50 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *p, int a);
extern void func_020027f0(int a);
extern void func_ov002_022080a0(void *p, int a);
extern void func_ov109_0229c28c(void *p, int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern int func_ov002_02207f60(void *p);

typedef struct {
    char pad_00[0x29b8];
    int unk_29B8;
} UnkStruct_0229d590;

void func_ov109_0229d590(UnkStruct_0229d590 *p)
{
    if (func_ov002_02207f3c(p, 0) != 0) {
        func_020027f0(6);
        func_ov002_022080a0(p, 5);
        func_ov109_0229c28c(p, 1);
        func_ov109_0229c28c(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, -16);
    }
    p->unk_29B8 = func_ov002_02207f60(p);
}
