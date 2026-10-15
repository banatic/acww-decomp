/* func_ov082_02278ef0 @ 0x02278ef0, 0x128 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *fn;
    unsigned char code;
} UnkStruct_02278ef0;

extern void *func_020984e8(void);
extern int func_02099640(void *);
extern void func_0209e474(void *);
extern int func_02099e9c(volatile unsigned short *);
extern unsigned char func_020952ec(void);
extern void func_02095764(volatile unsigned short *, unsigned char);
extern int func_0202ea80(int, int);
extern int func_02099fe8(void);

extern unsigned char data_ov082_022798c8[];
extern unsigned char data_ov082_022798d8[];

void func_ov082_02278ef0(void *obj, UnkStruct_02278ef0 *out)
{
    struct {
        volatile unsigned short h[4];
        int s[2];
    } L;
    unsigned char st;
    unsigned int ok;
    unsigned short v0, v1;
    unsigned int hit;

    func_02099640(func_020984e8());
    out->fn = (void *) data_ov082_022798c8;
    L.s[0] = 0;
    L.s[1] = 0;
    func_0209e474(L.s);
    if (*(int *) ((char *) obj + 0xc8) == -1) {
        L.h[1] = 0x37e0;
        *(int *) ((char *) obj + 0xc8) = func_02099e9c(&L.h[1]);
        if (*(int *) ((char *) obj + 0xc8) >= 0) {
            out->fn = (void *) data_ov082_022798d8;
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
        out->code = 3;
        func_02095764(&L.h[0], func_020952ec());
        if (func_0202ea80(0x1c, 0) == 0) {
            L.h[2] = 0x1376;
            ok = (func_02099e9c(&L.h[2]) < 0) ? 1 : 0;
            if (ok > 0) {
                hit = 0;
                v0 = L.h[0];
                v1 = L.h[0];
                if (v1 >= 0x1376 && v0 <= 0x1376) {
                    hit = 1;
                }
                if (hit == 0) {
                    L.h[3] = 0x1377;
                    ok = (func_02099e9c(&L.h[3]) < 0) ? 1 : 0;
                    if (ok > 0) {
                        hit = 0;
                        v0 = L.h[0];
                        v1 = L.h[0];
                        if (v1 >= 0x1377 && v0 <= 0x1377) {
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
    if (func_0202ea80(0x1c, 1) != 0) {
        out->code = 8;
    }
}
