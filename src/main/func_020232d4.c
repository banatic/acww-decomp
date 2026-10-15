/* func_020232d4 @ 0x020232d4, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020984e8(void);
extern void *func_02099640(int);
extern void func_02029264(void *a, void *b);
extern unsigned int func_0208150c(void *p);
extern void *func_020036e8(unsigned char *);
extern int func_0202da38(void *a, void *b, void *c, int d, void *e, int f, int g, int h, int i);

struct GlobalData {
    int x;
    unsigned char y;
};
extern struct GlobalData data_020c8e18;

struct UnkStruct_020232d4 {
    char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_020232d4_2 {
    char pad_00[0x100];
    void *unk_100;
    char buf_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_020232d4_3 {
    void *ptr;
    unsigned char byte;
};

void func_020232d4(struct UnkStruct_020232d4_2 *a, struct UnkStruct_020232d4_3 *out)
{
    func_02029264(a, (void *) ((char *) func_02099640((int) func_020984e8()) + 0xc0));
    func_0202da38(a, a->buf_104, &a->unk_122, 0x1e,
                  func_020036e8((unsigned char *) func_0208150c(((struct UnkStruct_020232d4 *) a->unk_100)->unk_830)),
                  data_020c8e18.x, data_020c8e18.y, 0, 0);
    out->ptr = a->buf_104;
    out->byte = a->unk_122;
}
