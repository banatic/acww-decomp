/* func_ov050_02263be4 @ 0x02263be4, 0x118 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern "C" int *func_02095794(int);
extern "C" void func_0201b458(void *out, void *obj, void *data);
extern "C" int func_0201c378(void *obj, int);
extern "C" void func_0204ed30(void *a, void *b);
extern "C" int func_02019e00(void *p);
extern "C" void func_02019d0c(void *p, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
extern "C" void func_0201b044(void *p, void *q);
extern "C" int func_020eaa6c(void *a, void *b);
extern "C" int func_020e8858(void *p);
extern "C" int func_0201c2a4(void *obj, int);
extern "C" void func_02016108(void *obj, int);
extern "C" void func_ov050_02264834(void *obj, int);
extern void *data_021c80bc;
extern unsigned short data_020c80f8;

class UnkStruct_02263be4 {
  public:
    virtual void m0();
    virtual void m1();
    virtual void m2();
};

extern "C" int func_ov050_02263be4(void *obj)
{
    int data[3];
    int out[3];
    int *p;
    int r4;
    int v;

    p = func_02095794(4);
    data[0] = p[0];
    data[1] = p[1];
    data[2] = p[2];

    func_0201b458(out, obj, data);

    r4 = func_0201c378(obj, 4);

    func_0204ed30(data_021c80bc, (char *) obj + 0x5c);

    if (r4 > 0x4000) {
        if (func_02019e00((char *) obj + 0x564) == 1) {
            func_02019d0c((char *) obj + 0x564, 2, 1, 0, 0, 0x800, 0, 0, 0, data_020c80f8, 0);
        }
    } else if (func_02019e00((char *) obj + 0x564) == 2) {
        func_02019d0c((char *) obj + 0x564, 1, 1, 0, 0, 0, 0, 0, 0, data_020c80f8, 0);
    }

    func_0201b044((char *) obj + 0x350, out);

    if (r4 > 0x3000) {
        if (func_020eaa6c(out, (char *) obj + 0x5c) == 0) {
            if (func_020e8858((char *) obj + 0x73d) != 0) {
                goto ret;
            }
        }
    }

    ((UnkStruct_02263be4 *) ((char *) obj + 0x658))->m2();

    v = func_0201c2a4(obj, 4);
    func_02016108((char *) obj + 0x658, v);

    func_ov050_02264834(obj, 4);

ret:
    return 1;
}
