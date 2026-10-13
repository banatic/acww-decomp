/* func_ov103_0229dbec @ 0x0229dbec, 0x74 bytes, Thumb, module ov103
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *addr, int value);
extern void func_ov103_0229c7ec(void *ptr);
extern int func_ov103_0229c2f4(void *ptr, int param);
extern int func_020ee45c(void *ptr);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *ptr, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *ptr, int a, int b, int c);
extern void func_ov002_02208090(void *ptr, int a);
extern int func_ov002_02207f60(void *ptr);

void func_ov103_0229dbec(void *ptr)
{
    func_ov002_02207d24((char *) ptr + 0x218c, 1);
    func_ov103_0229c7ec(ptr);
    if (func_ov103_0229c2f4(ptr, 0x100) == 0) {
        func_ov092_02299324(func_020ee45c(ptr), 0x44, 1);
    }
    func_ov002_02207f04(ptr, 8, 0, 0, 0x30);
    func_ov002_02207e80(ptr, 6, 0, 0);
    func_ov002_02208090(ptr, 4);
    *((int *) ((char *) ptr + 0x2b8c)) = func_ov002_02207f60(ptr);
}
