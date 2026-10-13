/* func_0201c9dc @ 0x0201c9dc, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0201cb68(unsigned char *p, int q);
extern void func_0201ca40(unsigned char *p, int q);

void func_0201c9dc(unsigned char *p, int q)
{
    if (func_0201cb68(p, q)) {
        if (*(unsigned char *) (p + 0x48) == 0) {
            func_0201ca40(p, q);
        }
        *(unsigned char *) (p + 0x48) = *(unsigned char *) (p + 0x48) + 1;
        if (*(unsigned char *) (p + 0x48) >= 14) {
            *(unsigned char *) (p + 0x48) = 0;
        }
    }
}
