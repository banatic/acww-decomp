/* func_ov068_02271f80 @ 0x02271f80, 0x8c bytes, Thumb, module ov068
 * mwccarm 1.2/base -O4,s
 */

extern void func_020109a0(void *p, int a, int b, int c);
extern void func_0200f268(void *p);
extern int func_02011368(void *p);
extern void func_0209e474(unsigned int *p);
extern void func_0209e140(unsigned int *p, int x);
extern void func_0200f7ac(void *p, int v, void *st);

void func_ov068_02271f80(void *p)
{
    struct {
        unsigned short flags;
        unsigned short pad;
        unsigned int a;
        unsigned int b;
    } st;
    int val;

    func_020109a0(p, 0x82, 0, 0);
    *((unsigned short *) ((char *) p + 0x8e)) = 0;
    func_0200f268(p);
    val = func_02011368(p);
    if (val != 0) {
        st.a = 0;
        st.b = 0;
        func_0209e474(&st.a);
        func_0209e140(&st.a, 1);
        st.flags = (st.flags & ~0x7f) | (((unsigned char *) &st)[9] & 0x7f);
        st.flags = (st.flags & 0xfffff87f) | ((((unsigned char *) &st)[8] & 0xf) << 7);
        st.flags = (st.flags & 0xffff07ff) | ((((unsigned char *) &st)[7] & 0x1f) << 0xb);
        func_0200f7ac(p, val, &st);
    }
}
