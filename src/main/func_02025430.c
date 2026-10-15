/* func_02025430 @ 0x02025430, 0x8c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0202d9c4(unsigned int *);
extern int func_0209bc40(unsigned char *);
extern unsigned int func_0208150c(void *arg);
extern int func_020036e8(void *object);
extern int func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);
extern void func_0209ba7c(void *arg);
extern void func_0207863c(void *arg);

typedef struct UnkStruct_02025430 {
    int x;
    unsigned char y;
} UnkStruct_02025430;

typedef struct UnkStruct_02025430_2 {
    char pad_00[0x100];
    void *unk_100;
    char unk_104[0x1E];
    unsigned char unk_122;
    char pad_123[0x41];
    void *unk_164;
} UnkStruct_02025430_2;

typedef struct UnkStruct_02025430_3 {
    void *ptr;
    unsigned char byte;
} UnkStruct_02025430_3;

extern UnkStruct_02025430 data_020c8d38;
extern UnkStruct_02025430 data_020c8cd0;

void func_02025430(UnkStruct_02025430_2 *p, UnkStruct_02025430_3 *out)
{
    int forwarded_value;

    UnkStruct_02025430 *r4 = &data_020c8d38;
    if (func_0209bc40((unsigned char *) func_0202d9c4((unsigned int *) p)) == 1) {
        r4 = &data_020c8cd0;
    }
    (forwarded_value = (int) func_0208150c(*(void **) ((char *) p->unk_100 + 0x830)));
    {
        int res = func_020036e8((void *) forwarded_value);
        func_0202da38(p, &p->unk_104, &p->unk_122, 0x1e, res, r4->x, r4->y, 0, 0);
    }
    out->ptr = &p->unk_104;
    out->byte = p->unk_122;
    func_0209ba7c(p->unk_164);
    func_0207863c(*(void **) ((char *) p->unk_100 + 0x830));
}
