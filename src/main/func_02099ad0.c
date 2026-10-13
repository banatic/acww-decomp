/* func_02099ad0 @ 0x02099ad0, 0xf8 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209526c(unsigned char *);
extern void func_02099e40(unsigned char *);
extern void func_02097dcc(unsigned char *);
extern void func_02088450(unsigned char *);
extern void func_02088760(unsigned char *);
extern void func_02088c0c(unsigned char *);
extern void func_020adf64(unsigned char *);
extern void func_02088808(unsigned char *);
extern void func_020983fc(unsigned char *);
extern void func_02077d24(unsigned char *);
extern void func_02077c0c(unsigned char *);
extern void func_0209ade4(unsigned char *);
extern void func_02097e18(unsigned char *);
extern void func_0203d388(unsigned char *);
extern void func_0203cfa0(unsigned char *);
extern void func_02138c48(unsigned char *, int, int, void (*)(void));
extern void func_020051b0(void);
extern void func_02066688(void);
extern void func_02072ce8(unsigned char *);

void *func_02099ad0(unsigned char *self)
{
    func_0209526c(self + 0x247e);
    func_02099e40(self + 0x245c);
    func_02097dcc(self + 0x243e);
    func_02088450(self + 0x242c);
    func_02088760(self + 0x2427);
    func_02088c0c(self + 0x2416);
    func_020adf64(self + 0x2404);
    func_02088808(self + 0x23ec);
    func_020983fc(self + 0x23e0);
    func_02077d24(self + 0x1f5c);
    func_02077c0c(self + 0x1f0c);
    func_0209ade4(self + 0x1e40);
    func_02097e18(self + 0x1d3c);
    func_0203d388(self + 0x1d3b);
    func_0203cfa0(self + 0x1c18);
    func_02138c48(self + 0x1bf2, 15, 2, func_020051b0);
    func_02138c48(self + 0x11a8, 10, 256, func_02066688);
    func_02072ce8(self);
    return self;
}