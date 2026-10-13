/* func_ov105_0229eefc @ 0x0229eefc, 0x94 bytes, Thumb, module ov105
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov105_0229d59c(void *p, unsigned char c);
extern int func_02065ec0(int a);
extern void func_020664a8(int a);
extern void func_ov105_0229c330(void *p, int a);
extern void func_0206e230(void *p, int a, int b, int c, int d);
extern void func_ov002_02207f20(void *p, int a, int b, int c, int d);
extern void func_02002708(int a);
extern void func_ov105_0229edc4(void *p);
extern void func_ov002_02208090(void *p, int a);
extern void func_ov002_0220b53c(void *p, int a);

void func_ov105_0229eefc(void *p)
{
    int a;
    int b;
    a = func_ov105_0229d59c(p, ((unsigned char *) p)[0x2bb]);
    b = func_02065ec0(a);
    if (b == 2 || b == 5 || b == 7) {
        func_ov105_0229c330(p, 0x1000);
    }
    func_020664a8(a);
    func_0206e230((char *) p + 0x2a18, a, 3, 4, 1);
    func_ov002_02207f20(p, 3, 0, 0, 0x30);
    func_02002708(3);
    func_02002708(4);
    func_ov105_0229edc4(p);
    func_ov002_02208090(p, 8);
    func_ov002_0220b53c((char *) p + 0x2d40, 0x88);
    func_ov105_0229c330(p, 0x80);
}
