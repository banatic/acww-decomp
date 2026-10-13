/* func_02025f78 @ 0x02025f78, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    void *p;
    unsigned char b;
} UnkStruct_02025f78;
extern struct {
    int a;
    unsigned char b;
} data_020c8d50;

extern void func_0208150c(int v);
extern int func_020036e8(void);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

void func_02025f78(void *self, UnkStruct_02025f78 *out)
{
    func_0208150c(*(int *) (*(char **) ((char *) self + 0x100) + 0x830));
    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 0x1e, func_020036e8(), data_020c8d50.a, data_020c8d50.b,
                  0, 0);
    out->p = (char *) self + 0x104;
    out->b = *((unsigned char *) self + 0x122);
    *(unsigned short *) ((char *) self + 0x15a) = 0x5e;
}
