/* func_ov004_02228dfc @ 0x02228dfc, 0x3c bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[12];
    unsigned short value;
    unsigned char pad_0E[14];
} UnkStruct_02228dfc;

extern unsigned int func_0200e92c(void *p);
extern void func_0200e90c(void *p, unsigned int val, void *b, void *c);
extern int func_0200e894(void *p, void *q);
extern int func_0200e91c(void *p);

int func_ov004_02228dfc(void *param0, unsigned short param1, void *param2, void *param3)
{
    UnkStruct_02228dfc stackVar;
    int result;

    func_0200e92c(&stackVar);
    func_0200e90c(&stackVar, 0x28, param2, param3);
    stackVar.value = param1;
    result = func_0200e894(param0, &stackVar);
    func_0200e91c(&stackVar);
    return result;
}
