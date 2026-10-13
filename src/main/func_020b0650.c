/* func_020b0650 @ 0x020b0650, 0x28 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char data[6];
} Elem;
extern int func_020b0a20(Elem *p);
extern void func_020b0a3c(Elem *p);

int func_020b0650(Elem *base, unsigned int index)
{
    Elem *p;
    if (index < 3) {
        p = &base[index];
        if (func_020b0a20(p) != 0) {
            func_020b0a3c(p);
            return 1;
        }
    }
    return 0;
}
