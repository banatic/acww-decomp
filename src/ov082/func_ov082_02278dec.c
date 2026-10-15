/* func_ov082_02278dec @ 0x02278dec, 0x104 bytes, Thumb, module ov082
 * mwccarm 1.2/base -O1,s
 */

extern void func_0208674c(volatile unsigned short *, void *);
extern void *func_020867e0(void *);
extern void *func_020867a0(void *);
extern void func_02015de4(void *, volatile unsigned short *, int, int);

extern int func_02086744(void *);
extern void func_02015fb0(void *, int, int, int, int, int);
extern int func_020951bc(void *);
extern void func_02015e40(void *, void *, int);
extern void *func_020984e8(void);
extern unsigned short *func_02099870(void *);
extern int memcmp(const void *, const void *, int);
extern int func_0209518c(void *, void *);
extern int func_02003704(void *);
extern void *func_02094fd4(void *);
extern int func_02003618(void *, void *);
extern void func_02068404(void *, int, void *);
extern void *func_02094fbc(void *);

extern unsigned char data_021f3aa4[];

int func_ov082_02278dec(void *obj)
{
    volatile unsigned short buf[2];
    char work[0x20];
    void *g;
    void *a, *b;
    unsigned short v0, v1;
    unsigned int ok;
    unsigned short *p, *q;

    g = (void *) data_021f3aa4;
    func_0208674c(&buf[0], g);
    ok = 0;
    v0 = buf[0];
    v1 = buf[0];
    if (v1 >= 0x12b0 && v0 <= 0x12e7) {
        ok = 1;
    }
    if (ok > 0) {
        a = func_020867e0(g);
        b = func_020867a0(g);
        func_0208674c(&buf[1], g);
        func_02015de4(obj, &buf[1], 1, 7);
        func_02015fb0(obj, func_02086744(g) >> 12, 0, 3, 0, 0);
        if (func_020951bc(a) != 0) {
            func_02015e40(obj, func_020867e0(g), 1);
            q = func_02099870(func_020984e8());
            p = func_020867e0(g);
            if (p[0] != q[0] || memcmp(p + 1, q + 1, 0xc) != 0 || func_0209518c(p, q) == 0) {
                return 1;
            }
            return 0;
        }
        if (func_02003704(b) != 0) {
            func_02094fd4(work);
            func_02003618(b, work);
            func_02068404(*(void **) ((char *) obj + 0x40), 1, work);
            func_02094fbc(work);
            return 2;
        }
    }
    return -1;
}
