/* func_02020c18 @ 0x02020c18, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_02020c18 {
    char pad_00[0x830];
    unsigned int value;
};

struct UnkStruct_02020c18_2 {
    char pad_00[0x100];
    struct UnkStruct_02020c18 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_02020c18_3 {
    void *ptr;
    unsigned char byte;
};

struct GlobalData {
    int word;
    unsigned char byte;
};

extern struct GlobalData data_020c8a98;
extern void func_0208150c(unsigned int, struct UnkStruct_02020c18 *);
extern int func_020036e8(void);
extern void func_0202da38(struct UnkStruct_02020c18_2 *, char *, unsigned char *, int, int, int, int, int, int);

void func_02020c18(struct UnkStruct_02020c18_2 *a, struct UnkStruct_02020c18_3 *out)
{
    func_0208150c(a->unk_100->value, a->unk_100);
    func_0202da38(a, a->unk_104, &a->unk_122, 30, func_020036e8(), data_020c8a98.word, data_020c8a98.byte, 0, 0);
    out->ptr = a->unk_104;
    out->byte = a->unk_122;
}
