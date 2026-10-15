/* func_0203d7d8 @ 0x0203d7d8, 0x5c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_0203d540(void *);
extern void func_0203d4d4(void *, int);
extern void func_020a8164(void *, void *);
extern void func_0203d4cc(void *, void *);
extern void func_0203d4d0(void *, int);
extern void func_0203d668(void *);
extern int func_0203d564(void *, void *);
extern void *func_0203d528(void *);

extern unsigned char data_021c69b4[];

int func_0203d7d8(void *a, unsigned char *b, void *c)
{
    struct {
        unsigned char pad[0x1e];
        unsigned char x;
        unsigned char pad2[0x11];
    } buf;
    int ret;

    func_0203d540(&buf);
    func_0203d4d4(&buf, 2);
    func_020a8164(&buf, c);
    func_0203d4cc(&buf, a);
    buf.x = *b;
    func_0203d4d0(&buf, 0);
    func_0203d668((void *) data_021c69b4);
    ret = func_0203d564((void *) data_021c69b4, &buf);
    func_0203d528(&buf);
    return ret;
}
