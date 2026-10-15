/* func_0201fe6c @ 0x0201fe6c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    int unk_00;
    unsigned char unk_04;
} GlobalData;
extern GlobalData data_020c8ce8;

typedef struct {
    void *ptr;
    unsigned char byte;
} Output;

void func_0201fe6c(void *self, Output *out)
{
    int a5 = func_020036e8(func_0208150c(*(int *) ((char *) *(void **) ((char *) self + 0x100) + 0x830)));
    int a6 = data_020c8ce8.unk_00;
    int a9 = data_020c8ce8.unk_04;
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, a5, a6, 1, 0xc, a9);
    out->ptr = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((char *) self + 0x122);
}
