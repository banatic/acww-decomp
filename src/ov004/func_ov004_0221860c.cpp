/* func_ov004_0221860c @ 0x0221860c, 0xc0 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 * compiler-emitted symbol: _ZN18Obj_ov004_0225305819func_ov004_0221860cEv
 */

#include "cpp/ov004/Obj_ov004_02253058.h"

typedef struct {
    int unk_00, unk_04;
} UnkStruct_0221860c;
extern "C" void func_ov004_0220cfec(void *p, int a);
extern "C" int func_ov004_0222c25c(void *t, unsigned int i);
extern "C" void func_0204f818(int *a, int *b, void *t);
extern "C" void func_ov004_0220db94(void *it);
extern "C" void func_ov004_0220f27c(void *s, void *it, int a, int b);
extern "C" UnkStruct_0221860c *func_ov004_0220db5c(void *it, unsigned int j);
extern "C" unsigned int func_ov004_0220db68(void *it);
extern "C" void func_ov004_0220db90(void *it);
extern "C" void func_ov004_0220d030(void *p);
extern "C" int func_ov004_0220ffbc(void *s);
extern "C" void func_ov004_022107d4(void *s);

int Obj_ov004_02253058::func_ov004_0221860c()
{
    char *s = (char *) this;
    int a;
    int b;
    char t[12];
    char it[36];
    unsigned int i;
    unsigned int j;
    int z;
    if (*(int *) (s + 0x780) == 0x2a) {
        func_ov004_0220cfec(s + 0x764, 0);
        z = 0;
        i = 0;
        do {
            if (func_ov004_0222c25c(t, i) != 0) {
                func_0204f818(&a, &b, t);
                func_ov004_0220db94(it);
                func_ov004_0220f27c(s, it, z, z);
                for (j = 0; j < func_ov004_0220db68(it); j++) {
                    if (a == func_ov004_0220db5c(it, j)->unk_00 && b == func_ov004_0220db5c(it, j)->unk_04) {
                        func_ov004_0220cfec(s + 0x764, 1);
                        func_ov004_0220d030(s + 0x860);
                        func_ov004_0220ffbc(s);
                        func_ov004_022107d4(s);
                        break;
                    }
                }
                func_ov004_0220db90(it);
            }
            i++;
        } while (i < 4);
    }
    ((Obj_ov004_02253058 *) s)->func_ov004_02218110();
    return 1;
}
