/* func_0207ab0c @ 0x0207ab0c, 0xc8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int data_021dc7bc;

extern void func_0209e474(void *p);
extern int func_0208150c(char *p);
extern int func_02003704(int x);
extern int func_0207f150(char *p);
extern void *func_02098844(int *g, int j);
extern int func_02099870(void *h);
extern int func_020951bc(int u);
extern int func_02099020(void *h, int n);
extern int func_02080998(char *p, int n, void *buf);
extern int func_02099174(void *h, int i);
extern int func_0205a1dc(int u, int t);
extern void func_02099164(void *h, int i, int v);

void func_0207ab0c(char *p)
{
    // DECLS
    int t;
    int jstart;
    int u;
    int v;
    int z;
    int buf[2];
    int i;
    int j;
    void *h;
    int w;
    // ENDDECLS

    buf[0] = 0;
    buf[1] = 0;
    func_0209e474(buf);
    jstart = 0;
    z = 0;
    for (i = 0; i < 8; i++) {
        t = func_0208150c(p);
        if (func_02003704(t)) {
            if (func_0207f150(p) == 3) {
                for (j = jstart; j < 4; j++) {
                    h = func_02098844(&data_021dc7bc, j);
                    if (h != 0) {
                        u = func_02099870(h);
                        if (func_020951bc(u)) {
                            if (func_02099020(h, 1) == 0) {
                                v = func_02080998(p, 7, buf);
                                if (v != ~z) {
                                    w = func_02099174(h, i);
                                    if (w != v) {
                                        if (func_0205a1dc(u, t)) {
                                            func_02099164(h, i, (unsigned char) v);
                                        }
                                    }
                                } else {
                                    func_02099164(h, i, 0xff);
                                }
                            }
                        }
                    }
                }
            }
        }
        p += 0x7ec;
    }
}
