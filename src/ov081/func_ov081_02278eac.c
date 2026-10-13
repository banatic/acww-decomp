/* func_ov081_02278eac @ 0x02278eac, 0x12c bytes, Thumb, module ov081
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *fn;
    unsigned char code;
} UnkStruct_02278eac;

extern void *func_020984e8(void);
extern void func_02099640(void *);
extern void func_0209e474(void *);
extern int func_02099e9c(volatile unsigned short *);
extern unsigned char func_020952ec(void);
extern void func_02095764(volatile unsigned short *, unsigned char);
extern int func_0202ea80(int, int);
extern int func_02099fe8(void);

extern unsigned char data_ov081_02279868[];
extern unsigned char data_ov081_02279878[];

void func_ov081_02278eac(void *obj, UnkStruct_02278eac *out)
{
    struct {
        volatile unsigned short h[6];
        int s[2];
    } L;
    unsigned char st;
    unsigned int ok;
    unsigned short v0, v1;
    unsigned int hit;

    func_02099640(func_020984e8());
    out->fn = (void *) data_ov081_02279868;
    L.s[0] = 0;
    L.s[1] = 0;
    func_0209e474(L.s);
    if (*(int *) ((char *) obj + 0xc8) == -1) {
        L.h[2] = 0x37e0;
        *(int *) ((char *) obj + 0xc8) = func_02099e9c(&L.h[2]);
        if (*(int *) ((char *) obj + 0xc8) >= 0) {
            out->fn = (void *) data_ov081_02279878;
            out->code = 0;
            return;
        }
    }
    st = ((unsigned char *) L.s)[2];
    if (st < 0xc || st >= 0x12) {
        out->code = 2;
        return;
    }
    {
        L.h[0] = 0x1374;
        func_02095764(&L.h[1], func_020952ec());
        out->code = 3;
        if (func_0202ea80(0x1b, 0) == 0) {
            L.h[3] = 0x1374;
            ok = (func_02099e9c(&L.h[3]) < 0) ? 1 : 0;
            if (ok > 0) {
                hit = 0;
                v0 = L.h[1];
                v1 = L.h[1];
                if (v1 >= 0x1374 && v0 <= 0x1374) {
                    hit = 1;
                }
                if (hit == 0) {
                    L.h[4] = 0x1375;
                    ok = (func_02099e9c(&L.h[4]) < 0) ? 1 : 0;
                    if (ok > 0) {
                        hit = 0;
                        v0 = L.h[1];
                        v1 = L.h[1];
                        if (v1 >= 0x1375 && v0 <= 0x1375) {
                            hit = 1;
                        }
                        if (hit == 0) {
                            if (func_02099fe8() >= 0) {
                                out->code = 1;
                            } else {
                                out->code = 0;
                            }
                            return;
                        }
                    }
                }
            }
        }
    }
    if (func_0202ea80(0x1b, 1) != 0) {
        out->code = 8;
    }
}
