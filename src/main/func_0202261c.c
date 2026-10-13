/* func_0202261c @ 0x0202261c, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *);
extern int func_020036e8(int);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    int word;
    unsigned char byte;
} Global;

extern Global data_020c8c80;

int func_0202261c(void *p)
{
    int a = func_020036e8(func_0208150c(*(void **) ((char *) *(void **) ((char *) p + 0x100) + 0x830)));
    {
        Global *gp = &data_020c8c80;
        func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 0x1e, a, gp->word, gp->byte, 0, 0);
    }
    return 1;
}
