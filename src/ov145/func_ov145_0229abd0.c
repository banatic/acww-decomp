/* func_ov145_0229abd0 @ 0x0229abd0, 0xdc bytes, Thumb, module ov145
 * mwccarm 1.2/base -O4,s
 */

extern int func_0206fe54(void *);
extern void func_ov002_02209eb8(void *);
extern int func_ov145_02299668(void *, int);
extern int func_ov002_02207f60(void *);
extern void func_ov002_0220ad18(void *, int);
extern void func_02088df8(int, void *, int, void *, int, int, int, int, int, int, int, int);
extern const unsigned char data_ov145_0229ae60[];
extern const unsigned char data_ov145_0229aea0[];

struct Vtbl12C {
    void (*slot0)(void *);
    void (*slot1)(void *);
    void (*slot2)(void *);
};
struct Obj12C {
    struct Vtbl12C *vtbl;
};

int func_ov145_0229abd0(void *self)
{
    struct Obj12C *obj;
    void *r7;
    const unsigned char *p;
    int i;
    int flag;

    if (func_0206fe54(self) != 0) {
        func_ov002_02209eb8((char *) self + 0xc8);
    }

    if (func_ov145_02299668(self, 1) == 0) {
        return 0;
    }

    func_ov002_0220ad18((char *) self + 0x174, func_ov002_02207f60(self));

    r7 = (char *) (*(void **) ((char *) self + 0x94)) + 0x60;

    if (*(int *) ((char *) self + 0xa4) > 0) {
        obj = (struct Obj12C *) ((char *) self + 0x12c);
        obj->vtbl->slot2(obj);
        func_02088df8(1, (void *) data_ov145_0229ae60, 0x80, r7, -1, 1, 0x1000, 0x1000, 0, -1, 0, 0);
    }

    p = data_ov145_0229aea0;
    for (i = 0; i < 4; i++) {
        flag = (i == *(unsigned char *) ((char *) self + 0xc1)) ? 7 : 5;
        func_02088df8(1, (void *) p, 0x80, r7, flag, 1, 0x1000, 0x1000, 0, -1, 0, 0);
        p += 0x10;
    }

    return 1;
}
