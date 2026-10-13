/* func_0208d290 @ 0x0208d290, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a144(void *);
extern void func_0208d15c(void *);
extern void func_0208e00c(void *);
extern void func_0208a1f4(void *);
extern void func_0208af00(void *);
extern void func_020edb3c(void *);

struct Sub1 {
    char pad_00[0x28];
};
struct Arr {
    char pad_00[0x1c];
};
struct UnkStruct_0208d290 {
    void *unk_00;
    char pad_04[8];
    struct Sub1 sub;
    struct Arr arr[4];
};

extern unsigned char data_020e2218[];

void *func_0208d290(struct UnkStruct_0208d290 *p)
{
    p->unk_00 = (void *) data_020e2218;
    func_0208a144(&p->sub);
    func_0208d15c(p);
    func_0208e00c(&p->arr[3]);
    func_0208e00c(&p->arr[2]);
    func_0208e00c(&p->arr[1]);
    func_0208e00c(&p->arr[0]);
    func_0208a1f4(&p->sub);
    func_0208af00(p);
    func_020edb3c(p);
    return p;
}
