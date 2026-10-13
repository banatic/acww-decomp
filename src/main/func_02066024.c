/* func_02066024 @ 0x02066024, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094fd4(void *);
extern void func_02095074(int, void *);
extern void func_0203d73c(void *);
extern void func_02094fbc(void *);
extern void func_0203d930(int, int, int, int *, int, int);
extern void func_02066088(int, int, int, int, int, int, int, int);

extern unsigned char data_021cd8c4[];
extern unsigned char data_021cd8ec[];
extern unsigned char data_021cd9b0[];

void func_02066024(int p1, int p2, int p3, int p4, int p5, int p6)
{
    int tmp;
    struct {
        char data[0x20];
    } local;

    func_02094fd4(&local);
    func_02095074(p6, &local);
    func_0203d73c(&local);
    func_02094fbc(&local);
    func_0203d930((unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, &tmp, p2, p3);
    func_02066088(p1, (unsigned int) data_021cd8c4, (unsigned int) data_021cd9b0, (unsigned int) data_021cd8ec, tmp, p4, p5,
                  p6);
}
