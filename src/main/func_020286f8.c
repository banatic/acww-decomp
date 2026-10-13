/* func_020286f8 @ 0x020286f8, 0x98 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020644cc(int a);
extern void func_0208150c(void *p);
extern int func_020036e8(void);
extern void func_0202da38(void *a, void *b, void *c, int d, int e, int f, int g, int h, int i);

extern unsigned char data_020d8d28[];
extern struct {
    unsigned int word;
    unsigned char byte;
} data_020c8c28;

struct UnkStruct_020286f8 {
    unsigned char pad_00[0x830];
    void *unk_830;
};

struct UnkStruct_020286f8_2 {
    unsigned char pad_00[0x100];
    struct UnkStruct_020286f8 *sub;
    void *unk_104;
    unsigned char pad_108[0x1A];
    unsigned char unk_122;
    unsigned char pad_123[0x35];
    unsigned char unk_158;
    unsigned char unk_159;
};

struct UnkStruct_020286f8_3 {
    void *ptr;
    unsigned char byte;
};

void func_020286f8(struct UnkStruct_020286f8_2 *obj, struct UnkStruct_020286f8_3 *out)
{
    int local0;
    int local1;
    int local2;
    int local3;
    int local4;
    unsigned char table[3];

    table[0] = data_020d8d28[0];
    table[1] = data_020d8d28[1];
    table[2] = data_020d8d28[2];

    obj->unk_159 = (unsigned char) func_020644cc(3);
    obj->unk_158 = table[obj->unk_159];

    func_0208150c(obj->sub->unk_830);

    local0 = func_020036e8();
    local1 = data_020c8c28.word;
    local2 = data_020c8c28.byte;
    local3 = (int) obj->unk_159;
    local4 = 0;

    func_0202da38(obj, &obj->unk_104, &obj->unk_122, 30, local0, local1, local2, local3, local4);

    out->ptr = &obj->unk_104;
    out->byte = obj->unk_122;
}
