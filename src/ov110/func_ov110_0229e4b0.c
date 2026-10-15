/* func_ov110_0229e4b0 @ 0x0229e4b0, 0x4a bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f3c(void *, int);
extern void func_020027f0(int);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov110_0229c2a8(void *, int);
extern void func_ov002_02207e80(void *, int, int, int);
extern int func_ov002_02207f60(void *);

typedef struct {
    char pad_00[0x98];
    int unk_98;
} UnkStruct_0229e4b0;

void func_ov110_0229e4b0(UnkStruct_0229e4b0 *p)
{
    if (func_ov002_02207f3c(p, 0)) {
        func_020027f0(6);
        func_ov002_022080a0((void *) (p), 5);
        func_ov110_0229c2a8(p, 1);
        func_ov110_0229c2a8(p, 2);
    } else {
        func_ov002_02207e80(p, 6, 0, 0);
    }
    p->unk_98 = func_ov002_02207f60(p);
}
