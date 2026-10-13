/* func_0205ebb4 @ 0x0205ebb4, 0x9c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_021ca16c[];
extern void func_0206060c(char *);
extern void *func_0205f100(char *, unsigned char);
extern int func_0205f64c(void *);
extern int func_0205f130(char *, unsigned char);
extern void func_0205502c(int);
extern void func_0205f120(char *, unsigned char, int);
extern void func_02055454(int);
extern void func_0205f0c0(char *, unsigned char);
extern int func_0205f2e8(char *, unsigned char);
extern void func_020e9b9c(int);
extern void func_0205f2c8(char *, unsigned char, int, int);
extern void func_0205f298(char *, unsigned char, int, int);
extern void func_0205f274(char *, unsigned char, int);

typedef struct {
    unsigned char unk_00;
    char pad_01[0x1f];
    int unk_20;
    int unk_24;
    char sub[1];
} UnkStruct_0205ebb4;

void func_0205ebb4(UnkStruct_0205ebb4 *p)
{
    volatile int unused;
    unsigned char v;

    func_0206060c(p->sub);
    v = p->unk_00;
    if (func_0205f64c(func_0205f100(data_021ca16c, v)) != 0x2b) {
        func_0205502c(func_0205f130(data_021ca16c, v));
        p->unk_20 = 0;
        p->unk_24 = 0;
    }
    func_0205f120(data_021ca16c, v, 0);
    func_02055454(func_0205f130(data_021ca16c, v));
    func_0205f0c0(data_021ca16c, v);
    func_020e9b9c(func_0205f2e8(data_021ca16c, v));
    func_0205f2c8(data_021ca16c, v, 0, 0);
    func_0205f298(data_021ca16c, v, 0, 0);
    func_0205f274(data_021ca16c, v, 0);
    *((unsigned short *) func_0205f100(data_021ca16c, v)) = 0xfff1;
    p->unk_00 = 9;
}
