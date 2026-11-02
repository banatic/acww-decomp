/* res_rows_files: 3 functions, module ov139
 * mwccarm 1.2/base -O4,s
 * func_ov139_022999f8 @ 0x022999f8, 0x70 bytes, Thumb
 * func_ov139_022999c4 @ 0x022999c4, 0x32 bytes, Thumb
 * func_ov139_02299964 @ 0x02299964, 0x60 bytes, Thumb
 */

struct UnkStruct_022999f8 {
    char pad_00[0x960];
    unsigned char unk_960[0x20];
    unsigned char unk_980[0x20];
    char pad_9A0[2];
    unsigned char unk_9A2;
};

extern const unsigned char data_ov139_02299e3c[];
extern const unsigned char data_ov139_02299e4c[];
extern const unsigned char data_ov139_02299e5c[];
extern void *data_021fbe94;
extern int func_02002c6c(const unsigned char *, void *, int, int, int, int);
extern int func_02002d14(const unsigned char *, void *, int, int, int, int);
extern int func_02064af4(const unsigned char *, void *, int);
extern void MIi_CpuCopy16(void *, void *, int);
extern void func_ov139_0229964c(void *, int, int, int);
extern void func_ov139_022995e4(void *, int, int, int);
extern unsigned char data_ov139_02299e00[];
extern unsigned char data_ov139_02299e14[];
extern unsigned char data_ov139_02299e28[];

void func_ov139_022999f8(struct UnkStruct_022999f8 *s)
{
    void *obj = data_021fbe94;
    func_02002c6c(data_ov139_02299e3c, obj, s->unk_9A2, 0x11, 0x11, 0x36);
    func_02002d14(data_ov139_02299e4c, obj, s->unk_9A2, 1, 1, 8);
    func_02064af4(data_ov139_02299e5c, s->unk_960, 0x20);
    MIi_CpuCopy16(s->unk_960, s->unk_980, 0x20);
}

void func_ov139_022999c4(void *p)
{
    int i;
    int a, b;
    i = 0;
    a = 0;
    b = 0;
    do {
        func_ov139_0229964c(p, i, a, 0xe);
        func_ov139_022995e4(p, i, b, 0xe);
        i++;
    } while (i < 6);
}

void func_ov139_02299964(void *receiver)
{
    void *obj = data_021fbe94;
    func_02002c6c((const unsigned char *) ((void *) data_ov139_02299e00), obj, 8, 0x80, 0x80, 0xff);
    func_02002c6c((const unsigned char *) ((void *) data_ov139_02299e14), obj, 8, 0x160, 0x160, 0x1ff);
    func_02002d14((const unsigned char *) ((void *) data_ov139_02299e28), obj, 8, 4, 4, 0xd);
}
