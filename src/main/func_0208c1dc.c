/* func_0208c1dc @ 0x0208c1dc, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2234;
extern void func_0208af30(void *);
extern void func_0208a1f8(void *);
extern void func_0208c834(void *);

struct Sub1 {
    char data[20];
};
struct Sub2 {
    char data[1];
};

struct UnkStruct_0208c1dc {
    void *vtbl;
    char pad_04[8];
    struct Sub1 sub1;
    int unk_20;
    char unk_24;
    char unk_25;
    char unk_26;
    char pad_27;
    struct Sub2 sub2;
};

struct UnkStruct_0208c1dc *func_0208c1dc(struct UnkStruct_0208c1dc *p)
{
    func_0208af30(p);
    p->vtbl = (void *) &data_020e2234;
    func_0208a1f8(&p->sub1);
    p->unk_20 = 0;
    p->unk_24 = 0;
    p->unk_25 = 0;
    p->unk_26 = 0;
    func_0208c834(&p->sub2);
    return p;
}
