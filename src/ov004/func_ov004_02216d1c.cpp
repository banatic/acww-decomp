/* func_ov004_02216d1c @ 0x02216d1c, 0xd4 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

#include "types.h"

typedef struct {
    int a, b;
} E;
typedef struct {
    int n;
    E e[4];
} List;

extern "C" {
extern void func_0203ee14(void *, void *);
extern void func_020a8164(void *, void *);
extern int func_ov004_0220fde0(void *);
extern u8 func_020b65c4(void);
extern char *func_ov004_0220db94(List *);
extern void func_ov004_0220db90(List *);
extern unsigned int func_ov004_0220db68(List *);
extern E *func_ov004_0220db5c(List *, unsigned int);
extern void func_ov004_0220f27c(void *, List *, int, int);
extern void *func_0204f5e0(void *, int, int, int, int, u8);
extern int func_0204bcdc(void *tile);
extern int data_ov004_02253200;
extern void *data_021c80bc;
}
extern "C"

    int
    func_ov004_02216d1c(char *self)
{
    // DECLS
    int bh;
    int v;
    int ah;
    int a;
    // A frame slot the code never uses; a pointer to a volatile local keeps it.
    volatile int dz[1];
    volatile int *dz_p = dz;
    List list;
    int b;
    void *p;
    void *g;
    void *tile;
    unsigned int i;
    // ENDDECLS

    p = self;
    if (self != 0) {
        p = self + 0xec;
    }
    func_0203ee14(self, p);
    *(int *) (*(char **) (self + 0x12c) + 8) = 1;
    func_020a8164(self + 0xec, &data_ov004_02253200);
    v = (func_ov004_0220fde0(self) + func_020b65c4()) & 0xf;
    func_ov004_0220db94(&list);
    func_ov004_0220f27c(self, &list, 0, 0);
    g = data_021c80bc;
    if (g != 0) {
        for (i = 0; i < func_ov004_0220db68(&list); i++) {
            a = func_ov004_0220db5c(&list, i)->a;
            b = func_ov004_0220db5c(&list, i)->b;
            ah = a >> 4;
            bh = b >> 4;
            if ((tile = func_0204f5e0(g, ah, bh, a - (ah << 4), b - (bh << 4), 0)) != 0 && func_0204bcdc(tile) != 0) {
                v = (v + (a + (b << 4))) & 0xf;
                break;
            }
        }
    }
    self[0x10a] = (char) v;
    func_ov004_0220db90(&list);
    return 1;
}
