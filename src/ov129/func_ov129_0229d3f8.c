/* func_ov129_0229d3f8 @ 0x0229d3f8, 0x48 bytes, Thumb, module ov129
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov002_02207f48(void *p, int a);
extern unsigned char *func_ov002_022080a0(void *object, unsigned char value);
extern void func_ov129_0229c820(void *p);
extern void func_ov129_0229b7dc(void *p, int a);
extern void func_ov129_0229bee4(void *p, int a);
extern int func_ov002_02207f60(void *p);

void func_ov129_0229d3f8(void *p)
{
    if (func_ov002_02207f48(p, 0)) {
        func_ov002_022080a0((void *) (p), 2);
        func_ov129_0229c820(p);
        func_ov129_0229b7dc(p, 0x10);
        func_ov129_0229bee4(p, 1);
    }
    *(int *) ((char *) p + 0xA0) = func_ov002_02207f60(p);
    *(int *) ((char *) p + 0x9C) = func_ov002_02207f60(p);
}
