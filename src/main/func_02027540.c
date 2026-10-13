/* func_02027540 @ 0x02027540, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_0208150c(void *a, void *b);
extern int func_020036e8(int a);
extern void func_0202da38(void *a, void *b, void *c, int d, ...);

extern struct {
    int field0;
    unsigned char field4;
} data_020c8e00;

typedef struct {
    void *ptr;
    unsigned char byte;
} UnkStruct_02027540;

void func_02027540(void *self, UnkStruct_02027540 *out)
{
    int local0, local1, local2, local3, local4;
    void *p1;
    void *p2;

    p1 = *(void **) ((char *) self + 0x100);
    p2 = *(void **) ((char *) p1 + 0x830);

    local0 = func_020036e8(func_0208150c(p2, p1));
    local1 = data_020c8e00.field0;
    local2 = data_020c8e00.field4;
    local3 = 0;
    local4 = 0;

    func_0202da38(self, (char *) self + 0x104, (char *) self + 0x122, 30, local0, local1, local2, local3, local4);

    out->ptr = (char *) self + 0x104;
    out->byte = *(unsigned char *) ((char *) self + 0x122);
}
