/* func_02009d90 @ 0x02009d90, 0x94 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_02056f94(void *);
extern int func_02008258(void *, int);
extern void func_0200c3b0(void *, int, int, int);
extern void func_02057bb8(unsigned short *);
extern void func_02057cb8(void *);

void func_02009d90(void *p)
{
    if (func_02056f94((char *) p + 0x2d0) != 0) {
        *(int *) ((char *) p + 0x7fc) = func_02008258(p, *(int *) ((char *) p + 0x7f0));
        func_0200c3b0(p, 3, 5, -1);
        if (*(signed char *) ((char *) p + 0x8eb) >= 0) {
            unsigned short val;
            func_02057bb8(&val);
            switch (val) {
                case 0x1373:
                    *(signed char *) ((char *) p + 0x8eb) = 3;
                    break;
                case 0x1375:
                    *(signed char *) ((char *) p + 0x8eb) = 2;
                    break;
                case 0x1377:
                    *(signed char *) ((char *) p + 0x8eb) = 1;
                    break;
                default:
                    break;
            }
        }
        func_02057cb8(p);
    }
}
