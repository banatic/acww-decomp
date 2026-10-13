/* func_ov086_02278ab8 @ 0x02278ab8, 0x6c bytes, Thumb, module ov086
 * mwccarm 1.2/base -O4,s
 */

extern int func_020160b4(int);
extern int func_020ab504(int);
extern int func_0209a050(int);
extern void func_02015330(int, unsigned short *, int, int, int);
extern void func_0206844c(int, void *, void *);
extern int data_ov086_02279438;
void func_ov086_02278ab8(int arg0)
{
    int val;
    int cond;
    void *ptr;
    int s;
    int unused;
    void *g;
    struct {
        unsigned char c;
        unsigned short h;
        int pad;
    } st;
    val = func_020ab504(func_020160b4(arg0));
    s = 0xff;
    cond = *((int *) (((char *) arg0) + 0xb4));
    if (cond < 0) {
        return;
    }
    ptr = (void *) (&data_ov086_02279438);
    g = ptr;
    if (((*((unsigned char *) (((char *) arg0) + 0x1e))) == 0) && (val == 0)) {
        if (cond >= 0) {
            func_0209a050(cond);
            st.h = 0x37e0;
            func_02015330(arg0, &st.h, 0, 5, 0);
        }
        s = 2;
    }
    if (s != 0xff) {
        st.c = (unsigned char) s;
        func_0206844c(*((int *) (((char *) arg0) + 0x40)), &st, g);
    }
}
