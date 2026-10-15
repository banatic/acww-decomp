/* func_02008dc0 @ 0x02008dc0, 0x3c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

typedef struct {
    unsigned char data[12];
    unsigned short unk_0C;
    unsigned char data2[14];
} UnkStruct_02008dc0;

int func_02008dc0(void *p0, unsigned short p1, int p2, int p3)
{
    UnkStruct_02008dc0 st;
    int ret;

    func_0200e92c(&st);
    func_0200e90c(&st, 0x77, p2, p3);
    st.unk_0C = p1;
    ret = func_0200e894(p0, &st);
    func_0200e91c(&st);
    return ret;
}
