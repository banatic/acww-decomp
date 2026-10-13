/* func_020259e4 @ 0x020259e4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct GlobalData {
    int value;
    unsigned char flag;
};
struct InnerB {
    char pad_00[0x830];
    int value;
};
struct MainA {
    char pad_00[0x100];
    void *unk_100;
};
struct UnkStruct_020259e4 {
    void *ptr;
    unsigned char byte;
};
extern struct GlobalData data_020c8aa0;
extern struct GlobalData data_020c8ae0;
extern int func_0208150c(int);
extern int func_020036e8(int);
extern void func_0202d9c4(void);
extern int func_0209bc40(void);
extern void func_0202da38(void *, void *, void *, int, int, int, int, int, int);
void func_020259e4(struct MainA *a, struct UnkStruct_020259e4 *out)
{
    struct GlobalData *g = &data_020c8aa0;
    int v1, v2, v3;
    func_0202d9c4();
    if (func_0209bc40() == 1) {
        g = &data_020c8ae0;
    }
    v1 = func_020036e8(func_0208150c(((struct InnerB *) a->unk_100)->value));
    v2 = g->value;
    v3 = g->flag;
    func_0202da38(a, (char *) a + 0x104, (char *) a + 0x122, 30, v1, v2, v3, 0, 0);
    out->ptr = (char *) a + 0x104;
    out->byte = *(unsigned char *) ((char *) a + 0x122);
}
