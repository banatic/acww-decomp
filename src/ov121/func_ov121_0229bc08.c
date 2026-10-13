/* func_ov121_0229bc08 @ 0x0229bc08, 0x68 bytes, Thumb, module ov121
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov121_0229b948(void *p);
extern void func_ov121_0229b8c0(void *p);
extern void func_ov121_0229b7d4(void *p);
extern void func_ov002_022097b8(void *p);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int x);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov121_02299a4c(void *p, int a);
extern void func_ov002_02207e80(void *p, int a, int b, int c);
extern void *func_ov002_02207f60(void *p);

void func_ov121_0229bc08(void *p)
{
    func_ov121_0229b948(p);
    func_ov121_0229b8c0(p);
    func_ov121_0229b7d4(p);
    func_ov002_022097b8((char *) p + 0x528);
    func_ov002_02207f20(p, 8, 0, 0, 0x30);
    func_02002708(6);
    func_ov002_02208090(p, 1);
    func_ov121_02299a4c(p, 1);
    func_ov002_02207e80(p, 6, 0, 0);
    *(void **) ((char *) p + 0x94) = func_ov002_02207f60(p);
}
