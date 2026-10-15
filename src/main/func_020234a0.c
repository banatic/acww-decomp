/* func_020234a0 @ 0x020234a0, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(int);
extern int func_020036e8(int);
extern int func_0202da38(void *, void *, void *, int, int, int, int, int, int);

typedef struct {
    unsigned int a;
    unsigned char b;
} GlobalData;
extern GlobalData data_020c8bc0;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_020234a0;

void func_020234a0(void *p, UnkStruct_020234a0 *out)
{
    int val0;

    val0 = func_020036e8(func_0208150c(*(unsigned int *) ((char *) *(unsigned int *) ((char *) p + 0x100) + 0x830)));
    func_0202da38(p, (char *) p + 0x104, (char *) p + 0x122, 0x1e, val0, data_020c8bc0.a, data_020c8bc0.b, 0, 0);
    out->ptr = (char *) p + 0x104;
    out->byte = *(unsigned char *) ((char *) p + 0x122);
}
