/* func_ov111_022a08bc @ 0x022a08bc, 0x54 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov095_0229c420(char *p, int v);
extern void func_ov111_0229f084(char *p);
extern void func_ov111_0229efc8(char *p, int v);
extern void func_ov002_02207f20(char *p, int a, int b, int c, int d);
extern void func_02002708(int v);
extern void func_ov002_02207e80(char *p, int a, int b, int c);
extern void func_ov002_02208090(char *p, int v);
extern void func_ov111_0229fd08(char *p);

void func_ov111_022a08bc(char *param0)
{
    func_ov095_0229c420(param0 + 0xac, 6);
    func_ov111_0229f084(param0);
    func_ov111_0229efc8(param0, 4);
    func_ov002_02207f20(param0, 8, 3, 0, 0x30);
    func_02002708(6);
    func_ov002_02207e80(param0, 6, 0, 0);
    func_ov002_02208090(param0, 3);
    func_ov111_0229fd08(param0);
}
