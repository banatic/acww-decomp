/* func_02020490 @ 0x02020490, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int a, void *b);
extern int func_020036e8(int a);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern int data_020c8ab0;

struct Output {
    void *ptr;
    unsigned char byte;
};

void func_02020490(void *A, struct Output *B)
{
    int *p = *(int **) ((char *) A + 0x100);
    int r1 = func_020036e8(func_0208150c(*(int *) ((char *) p + 0x830), p));
    func_0202da38(A, (char *) A + 0x104, (char *) A + 0x122, 0x1e, r1, data_020c8ab0, 1, 0xc, 2);
    B->ptr = (char *) A + 0x104;
    B->byte = *(unsigned char *) ((char *) A + 0x122);
}
