/* func_02077f8c @ 0x02077f8c, 0x8a bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02070c08(void *);
extern void func_020707d0(void *);
extern short *func_020782cc(int);
extern int func_020a7bf4(void *, int);
extern void func_020a8a34(void *, int);
extern void func_020a87e0(void *, void *);
extern void func_0205182c(void *, short *, int);
extern int func_02070784(void *);
extern void func_020a8c1c(void *);
extern void func_020707b8(void *);
extern void func_02070be8(void *);
int func_02077f8c(int a, void *b)
{
    char v1[0x6c];
    char v2[0x60];
    short *p;
    int cnt;
    int i;
    func_02070c08(v1);
    func_020707d0(v2);
    p = func_020782cc(a);
    cnt = 0;
    for (i = cnt; i < 6; i++) {
        int r = func_020a7bf4((char *) b + 0x12, i);
        if (r != 0) {
            int n;
            func_020a8a34(v1, r);
            func_020a87e0(v2, v1);
            func_0205182c(v2, p + cnt, 0x10);
            n = func_02070784(v2);
            cnt += n;
            if (n != 0x10) {
                p[cnt] = 0xa;
                cnt++;
            }
        } else {
            func_020a8c1c(v1);
            p[cnt] = 0xa;
            cnt++;
        }
    }
    func_020707b8(v2);
    func_02070be8(v1);
    return 1;
}
