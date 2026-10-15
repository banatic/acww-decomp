/* func_0202365c @ 0x0202365c, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_0202365c_2 {
    char pad_00[0x830];
    unsigned int unk_830;
};

struct UnkStruct_0202365c {
    char pad_00[0x100];
    struct UnkStruct_0202365c_2 *unk_100;
    char unk_104[0x1e];
    unsigned char unk_122;
};

struct UnkStruct_0202365c_3 {
    unsigned int unk_00;
    unsigned char unk_04;
};

struct UnkStruct_0202365c_4 {
    char *data;
    unsigned char length;
};

extern unsigned int func_0208150c(unsigned int);
extern unsigned int func_020036e8(unsigned int);
extern int func_0202da38(struct UnkStruct_0202365c *p, char *buf, unsigned char *len, int maxlen, int base, int offset,
                         int scale, int multiplier, int selected);
extern struct UnkStruct_0202365c_3 data_020c89c0;

void func_0202365c(struct UnkStruct_0202365c *p, struct UnkStruct_0202365c_4 *out)
{
    unsigned int local0;
    unsigned int local1;
    unsigned int local2;
    unsigned int local3;
    unsigned int local4;

    local0 = func_020036e8(func_0208150c(p->unk_100->unk_830));
    local1 = data_020c89c0.unk_00;
    local2 = data_020c89c0.unk_04;
    local3 = 0;
    local4 = 0;
    func_0202da38(p, p->unk_104, &p->unk_122, 0x1e, local0, local1, local2, local3, local4);
    out->data = p->unk_104;
    out->length = p->unk_122;
}
