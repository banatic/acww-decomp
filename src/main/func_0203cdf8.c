/* func_0203cdf8 @ 0x0203cdf8, 0x140 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02061b1c(unsigned short *, int, int);
extern int func_0204bcdc(unsigned short *);
extern int func_0204bc64(unsigned short *);
extern int func_0204bd5c(unsigned short *);

char *func_0203cdf8(int base, unsigned char *out, int code)
{
    unsigned short h;

    func_02061b1c(&h, code, 1);
    if (func_0204bcdc(&h)) {
        int val;
        val = func_0204bc64(&h);
        *out = (unsigned char) (1 << (val & 7));
        return (char *) (base + (val >> 3));
    } else {
        int cond1;
        int delta;

        cond1 = (h >= 0x1100 && h <= 0x1143);
        if (cond1) {
            delta = (h >= 0x1100 && h <= 0x1143) ? h - 0x1100 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x100 + (delta >> 3));
        } else if (h >= 0x1144 && h <= 0x1187) {
            delta = (h >= 0x1144 && h <= 0x1187) ? h - 0x1144 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x109 + (delta >> 3));
        } else if (h >= 0x1323 && h <= 0x1368) {
            delta = (h >= 0x1323 && h <= 0x1368) ? h - 0x1323 : -1;
            *out = (unsigned char) (1 << (delta & 7));
            return (char *) (base + 0x112 + (delta >> 3));
        } else if (h >= 0x1000 && h <= 0x10ff) {
            int val;
            val = func_0204bd5c(&h);
            *out = (unsigned char) (1 << (val & 7));
            return (char *) (base + 0x11b + (val >> 3));
        } else {
            *out = 0;
            return 0;
        }
    }
}
