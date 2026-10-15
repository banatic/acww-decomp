/* func_020284c0 @ 0x020284c0, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int data_020c8c48[];
extern unsigned int data_020c8a90[];
extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int offset, int scale, int h, int i);

void func_020284c0(char *p1, char *p2)
{
    unsigned int *msg = 0;
    int val;

    switch (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p1))) {
        case 0xa:
            msg = data_020c8c48;
            break;
        case 0x13:
            msg = data_020c8a90;
            break;
    }
    if (msg != 0) {
        val = func_020036e8(func_0208150c(*(int *) (*(int *) (p1 + 0x100) + 0x830)));
        func_0202da38(p1, p1 + 0x104, p1 + 0x122, 0x1e, val, msg[0], *(unsigned char *) (msg + 1), 0, 0);
    }
    *(void **) p2 = p1 + 0x104;
    *(unsigned char *) (p2 + 4) = *(unsigned char *) (p1 + 0x122);
    *(unsigned short *) (p1 + 0x15a) = 0x5e;
}
