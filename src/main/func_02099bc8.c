/* func_02099bc8 @ 0x02099bc8, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void *func_02072d14(void *);
extern void __cxa_vec_ctor(void *, int, int, void (*)(void *), void (*)(void *));
extern void func_02066688(void *);
extern void func_02066694(void *);
extern void func_020051b0(void *);
extern void func_02034ce0(void *);
extern void func_0203cfa4(void *);
extern void func_0203d38c(void *);
extern void *func_02097e28(void *);
extern void *func_0209ae20(void *);
extern void *func_02077c20(void *);
extern void *func_02077d40(void *);
extern void func_02098400(void *);
extern void func_0208880c(void *);
extern int func_020adf74(void *);
extern void func_02088c10(void *);
extern void func_02088764(void *);
extern int func_02088460(void *);
extern void func_02097dd0(void *);
extern void *func_02099e58(void *);
extern void *func_0209529c(void *);

void *func_02099bc8(void *p)
{
    void *sub;
    unsigned short val;

    func_02072d14(p);
    sub = (char *) p + 0x11a8;
    __cxa_vec_ctor((void *) (sub), 0xa, 0x100, (void (*)(void *)) func_02066694, (void (*)(void *)) func_02066688);
    __cxa_vec_ctor((void *) ((char *) sub + 0xa4a), 0xf, 2, (void (*)(void *)) func_02034ce0,
                   (void (*)(void *)) func_020051b0);
    func_0203cfa4((char *) p + 0x1c18);
    func_0203d38c((char *) p + 0x1d3b);
    func_02097e28((char *) p + 0x1d3c);
    func_0209ae20((char *) p + 0x1e40);
    func_02077c20((char *) p + 0x1f0c);
    func_02077d40((char *) p + 0x1f5c);
    func_02098400((char *) p + 0x23e0);
    func_0208880c((char *) p + 0x23ec);
    func_020adf74((char *) p + 0x2404);
    val = 0xfff1;
    *((unsigned short *) ((char *) p + 0x2406)) = val;
    *((unsigned short *) ((char *) p + 0x2408)) = val;
    *((unsigned short *) ((char *) p + 0x240a)) = val;
    *((unsigned short *) ((char *) p + 0x240c)) = val;
    *((unsigned short *) ((char *) p + 0x240e)) = val;
    *((unsigned short *) ((char *) p + 0x2410)) = val;
    func_02088c10((char *) p + 0x2416);
    func_02088764((char *) p + 0x2427);
    func_02088460((char *) p + 0x242c);
    func_02097dd0((char *) p + 0x243e);
    func_02099e58((char *) p + 0x245c);
    func_0209529c((char *) p + 0x247e);
    return p;
}
