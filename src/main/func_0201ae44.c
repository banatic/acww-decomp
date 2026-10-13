/* func_0201ae44 @ 0x0201ae44, 0x48 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char data[12];
} UnkStruct_0201ae44;
typedef struct {
    char data[12];
} GEntry;

struct Param {
    char pad_00[0x5C];
    char unk_5C;
    char pad_5D[0x94 - 0x5C - 1];
    short unk_94;
};

extern GEntry data_021c16e4[];
extern void func_0201af58(void *out, void *in, GEntry *entry, short s);
extern int func_0201ae8c(void *ptr);

void func_0201ae44(unsigned char *flags, struct Param *p)
{
    int i;
    for (i = 0; i < 2; i++) {
        UnkStruct_0201ae44 tmp;
        func_0201af58(&tmp, &p->unk_5C, &data_021c16e4[i], p->unk_94);
        if (func_0201ae8c(&tmp)) {
            *flags |= (1 << i);
        }
    }
}
