/* func_ov099_0229da84 @ 0x0229da84, 0x64 bytes, Thumb, module ov099
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207d24(void *addr, int value);
extern void func_ov099_0229c754(void *obj);
extern int func_020ee45c(void *obj);
extern void func_ov092_02299324(int a, int b, int c);
extern void func_ov002_02207f04(void *obj, int a, int b, int c, int d);
extern void func_ov002_02207e80(void *obj, int a, int b, int c);
extern void func_ov002_02208090(void *obj, int a);
extern int func_ov002_02207f60(void *obj);

void func_ov099_0229da84(void *obj)
{
    func_ov002_02207d24((char *) obj + 0x218C, 1);
    func_ov099_0229c754(obj);
    func_ov092_02299324(func_020ee45c(obj), 0x44, 1);
    func_ov002_02207f04(obj, 8, 0, 0, 0x30);
    func_ov002_02207e80(obj, 6, 0, 0);
    func_ov002_02208090(obj, 4);
    *(int *) ((char *) obj + 0x27EC) = func_ov002_02207f60(obj);
}
