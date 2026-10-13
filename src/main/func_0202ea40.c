/* func_0202ea40 @ 0x0202ea40, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0209e474(void *);
extern int func_02088470(unsigned char, unsigned char, unsigned char, void *);

typedef struct {
    unsigned char f : 2;
} TwoBit;

int func_0202ea40(int unused, TwoBit *p, int expected)
{
    unsigned int local[2];
    local[0] = 0;
    local[1] = 0;
    func_0209e474(local);
    if (func_02088470(((unsigned char *) local)[5], ((unsigned char *) local)[4], ((unsigned char *) local)[3], p) &&
        (p->f == expected)) {
        return 1;
    }
    return 0;
}
