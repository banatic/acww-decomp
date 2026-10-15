/* func_02077f3c @ 0x02077f3c, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_020780d0(void *);
extern void func_02078070(void *, int, int);
extern int func_02078148(const void *);
extern void func_020782a0(int, void *);
extern int func_02077f8c(int, void *);
extern void *func_020780b8(void *);
extern int data_021eed68;

void *func_02077f3c(int a, int b, unsigned char c, unsigned char d, unsigned char e)
{
    struct {
        unsigned char x;
        unsigned char y;
        unsigned char z;
    } small;
    int buf[54];
    int temp;

    func_020780d0(buf);
    func_02078070(buf, a, b);
    temp = func_02078148(&data_021eed68);
    small.z = c;
    small.y = d;
    small.x = e;
    func_020782a0(temp, &small);
    func_02077f8c(temp, buf);
    return func_020780b8(buf);
}
