/* func_0202c424 @ 0x0202c424, 0x158 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Node Node;
struct NodeVT {
    void *pad_00[25];
    void *(*unk_64)(Node *);
};
struct Node {
    struct NodeVT *vt;
};

typedef struct {
    char pad_00[0x100];
    Node *unk_100;
    char pad_104[0x28];
    void *unk_12C;
} UnkStruct_0202c424;

typedef struct {
    int a, b;
} St;
typedef struct {
    char pad_00[0x1d];
    unsigned char b0 : 2;
    unsigned char b2 : 1;
} UnkStruct_0202c424_2;

extern void *func_020984e8(void);
extern void *func_02099870(void *);
extern int func_020951bc(void *);
extern int func_02094ffc(void *);
extern unsigned short *func_02095040(void *);
extern void *func_02081d60(void *);
extern unsigned short *func_02081d64(void *);
extern void *func_02081e10(void *);
extern int memcmp(const void *, const void *, unsigned int);
extern void func_0209e474(St *);
extern int func_0209e3ac(void *, St *, int);
extern int func_0209e380(void *, St *);
extern void *func_0208150c(void *);
extern int func_02003704(void *);
extern UnkStruct_0202c424_2 *func_0207f270(void *);
extern unsigned short data_021dc7aa[7];

int func_0202c424(UnkStruct_0202c424 *s, int *out)
{
    unsigned long long self = (unsigned long) s;
    unsigned long long output = (unsigned long) out;
    St st;
    void *h;
    void *a;
    unsigned short *p;
    unsigned short *identity;
    unsigned short *q;
    unsigned short *g;
    void *n;
    int flag;

    if (func_020984e8() != 0) {
        a = func_02099870(func_020984e8());
    } else {
        a = 0;
    }
    st.a = 0;
    identity = data_021dc7aa;
    st.b = 0;
    if (((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C == 0) {
        return 0;
    }
    if (a != 0 && func_020951bc(a) != 0 && func_02094ffc(a) != 0) {
        p = func_02095040(a);
        q = func_02095040(func_02081d60(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C));
        if (q[0] != p[0] || memcmp((char *) q + 2, (char *) p + 2, 0xc) != 0) {
            return 6;
        }
    }
    func_0209e474(&st);
    h = func_02081e10(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C);
    g = (unsigned short *) (char *) &data_021dc7aa[0];
    if (g != 0) {
        q = func_02081d64(((UnkStruct_0202c424 *) (unsigned long) self)->unk_12C);
        if (data_021dc7aa[0] != q[0] || memcmp((char *) identity + 2, (char *) q + 2, 0xc) != 0) {
            return 5;
        }
    }
    if (func_0209e3ac(h, &st, 0x3f) == 1) {
        return 1;
    }
    n = ((UnkStruct_0202c424 *) (unsigned long) self)
            ->unk_100->vt->unk_64(((UnkStruct_0202c424 *) (unsigned long) self)->unk_100);
    flag = 0;
    if (n != 0 && func_02003704(func_0208150c(n)) != 0 && func_0207f270(n) != 0) {
        if (func_0207f270(n)->b2 != 0) {
            flag = 1;
        }
    }
    *(int *) (unsigned long) output = func_0209e380(h, &st);
    if (func_02094ffc(a) != 0) {
        if (*(int *) (unsigned long) output >= 1 && flag == 0) {
            return 1;
        }
        return 2;
    }
    if (*(int *) (unsigned long) output >= 0x1e) {
        return 4;
    }
    if (*(int *) (unsigned long) output >= 7) {
        return 3;
    }
    if (*(int *) (unsigned long) output >= 1 && flag == 0) {
        return 1;
    }
    return 2;
}
