/* func_0201f1f0 @ 0x0201f1f0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ba0;

struct UnkStruct_0201f1f0 {
    char *ptr;
    unsigned char byte;
};

void func_0201f1f0(void *a, struct UnkStruct_0201f1f0 *b)
{
    int v0;
    int v1;

    v0 = func_020036e8(func_0208150c(*(int *) (*(int *) ((char *) a + 0x100) + 0x830)));
    v1 = data_020c8ba0;
    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, v0, v1, 1, 13, 2);
    b->ptr = (char *) a + 0x104;
    b->byte = *((unsigned char *) a + 0x122);
}
