/* func_0207a8ac @ 0x0207a8ac, 0xb8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x7ec];
} UnkStruct_0207a8ac;

extern int func_020791ec(void);
extern int func_020791bc(void);
extern int func_0208150c(void *p);
extern int func_02003704(int x);
extern int func_0207f270(void *p);
extern int func_02079544(int x);
extern void func_02079500(int x);
extern void func_02079540(int x, int y);
extern void *func_0207cec0(void *p, int id);
extern void func_02079204(int x);
extern void func_020791d4(int x);

void func_0207a8ac(UnkStruct_0207a8ac *self)
{
    int id1;
    int id2;
    UnkStruct_0207a8ac *s;
    int i;
    void *p;

    id1 = func_020791ec();
    id2 = func_020791bc();
    s = self;
    for (i = 0; i < 8; i++) {
        if (func_02003704(func_0208150c(s)) && func_02079544(func_0207f270(s)) == 3) {
            func_02079500(func_0207f270(s));
        }
        s++;
    }

    if (id1 != -1) {
        p = func_0207cec0(self, id1);
        if (p != 0 && func_02003704(func_0208150c(p))) {
            func_02079540(func_0207f270(p), 0);
            p = func_0207cec0(self, id2);
            if (p != 0 && func_02003704(func_0208150c(p))) {
                func_02079540(func_0207f270(p), 3);
            }
        } else {
            func_02079204(-1);
            func_020791d4(-1);
        }
    }
}