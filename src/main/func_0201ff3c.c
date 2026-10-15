/* func_0201ff3c @ 0x0201ff3c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);
extern int data_020c8ce8;

struct Dst {
    void *ptr;
    unsigned char byte;
};

void func_0201ff3c(void *src, struct Dst *dst)
{
    int tmp;
    tmp = func_020036e8(func_0208150c(*(int *) ((char *) (*(char **) ((char *) src + 0x100)) + 0x830)));
    func_0202da38(src, (char *) src + 0x104, (char *) src + 0x122, 30, tmp, data_020c8ce8, 1, 7, 3);
    dst->ptr = (char *) src + 0x104;
    dst->byte = *((unsigned char *) src + 0x122);
}
