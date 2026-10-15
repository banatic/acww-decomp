/* func_ov109_0229d6a0 @ 0x0229d6a0, 0x90 bytes, Thumb, module ov109
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov109_0229d3e8(void *obj);
extern int func_ov002_0220ab84(void *ptr, int a);
extern void func_ov094_0229ad20(void *ptr);
extern void func_ov109_0229cb10(void *obj);
extern void func_ov094_0229b2b0(void *ptr);
extern void func_ov094_0229b794(void *ptr, int a);
extern void func_ov002_02207f20(void *obj, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov002_02207e80(void *obj, int a, int b, int c);
extern void func_ov002_02208090(void *obj, int a);
extern void func_ov109_0229c29c(void *obj, int a);
extern int func_ov002_02207f60(void *obj);

void func_ov109_0229d6a0(void *obj)
{
    int zero = 0;
    func_ov109_0229d3e8(obj);
    func_ov002_0220ab84((char *) obj + 0x27e8, 0x65);
    func_ov094_0229ad20((char *) obj + 0xcc);
    func_ov109_0229cb10(obj);
    func_ov094_0229b2b0((char *) obj + 0xb2c);
    func_ov094_0229b794((char *) obj + 0xb2c, 0xf);
    func_ov002_02207f20(obj, 8, zero, zero, 0x30);
    func_02002708(6);
    func_ov002_02207e80(obj, 6, 0, -16);
    func_ov002_02208090(obj, 2);
    func_ov109_0229c29c(obj, 1);
    func_ov109_0229c29c(obj, 2);
    *(int *) ((char *) obj + 0x29b8) = func_ov002_02207f60(obj);
}
