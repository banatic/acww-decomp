/* func_ov110_0229e564 @ 0x0229e564, 0x70 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov110_0229c2dc(unsigned int);
extern void func_ov110_0229cbe0(unsigned int);
extern int func_ov002_02207d24(char *, int);
extern int func_020ee45c(unsigned int);
extern void func_ov092_02299324(int, int, int);
extern void func_ov002_02207f04(unsigned int, int, int, int, int);
extern void func_ov002_02207e90(unsigned int, int);
extern void func_ov002_02207e80(unsigned int, int, int, int);
extern unsigned int func_ov002_02207f60(unsigned int);
extern void func_ov002_02208090(unsigned int, int);

void func_ov110_0229e564(unsigned int param0)
{
    if (func_ov110_0229c2dc(param0) != 0) {
        unsigned int value;
        char *p;

        func_ov002_02207d24((char *) param0 + 0x21f8, 1);
        func_ov110_0229cbe0(param0);
        func_ov092_02299324(func_020ee45c(param0), 0x44, 1);
        func_ov002_02207f04(param0, 2, 4, 1, 0x30);
        func_ov002_02207e90(param0, 0x80);
        func_ov002_02207e80(param0, 4, 0, 0);
        value = func_ov002_02207f60(param0);
        p = (char *) param0;
        p += 0x9c;
        *(unsigned int *) p = value;
        func_ov002_02208090(param0, 5);
    }
}
