/* func_02066228 @ 0x02066228, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094fd4(void *);
extern void func_02003618(int, void *);
extern void func_0203d7c4(int, void *);
extern void func_02094fbc(void *);
extern void func_02095074(int, void *);
extern void func_0203d73c(void *);
extern void func_0203d834(int, int, int, void *, int, int, int, int, int);
extern void func_02066344(int, int, int, int, int, int, int, int);

extern unsigned char data_021cd8c4[];
extern unsigned char data_021cd8ec[];
extern unsigned char data_021cd9b0[];

void func_02066228(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int tmp;
    char buf1[0x20];
    char buf2[0x20];

    if (a9 != 0xb) {
        func_02094fd4(buf1);
        func_02003618(a7, buf1);
        func_0203d7c4(a9, buf1);
        func_02094fbc(buf1);
    }

    func_02094fd4(buf2);
    func_02095074(a8, buf2);
    func_0203d73c(buf2);
    func_02094fbc(buf2);

    func_0203d834((unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, &tmp, a1, a2, a3,
                  a4, a5);
    func_02066344(a0, (unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, tmp, a6, a7,
                  a8);
}
