/* func_0201100c @ 0x0201100c, 0x70 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Sub5c {
    int pad_00;
    int ret;
} Sub5c;

typedef struct UnkStruct_0201100c {
    char pad_00[0x5c];
    Sub5c sub_5c;
    char pad_64[0x68 - 0x5c - 8];
    void *unk_68;
    char pad_6C[0x8e - 0x6c];
    signed short unk_8E;
    char pad_90[0x174 - 0x90];
    char unk_174;
    char pad_175[0x7a4 - 0x175];
    char unk_7A4;
    char pad_7A5[0x7f0 - 0x7a5];
    void *unk_7F0;
} UnkStruct_0201100c;

extern void func_02003300(void *, void *);
extern void *func_02032c64(void *);
extern int func_020082a0(void *, void *);
extern void func_02031288(void *, void *, void *, int, int, void *, int);
extern void *func_02032c50(void *);
extern int func_020310c8(int value);

int func_0201100c(UnkStruct_0201100c *self)
{
    int result;

    char buf[0x34];
    char *p5c;
    signed short s;
    void *a0;

    p5c = (char *) self + 0x5c;
    func_02003300(self, &self->unk_174);
    func_02032c64(buf);
    s = self->unk_8E;
    if (func_020082a0(self, self->unk_7F0) == 0) {
        a0 = buf;
    } else {
        a0 = &self->unk_7A4;
    }
    func_02031288(a0, p5c, (char *) self + 0x68, s, 0xfd7, self, 0xf);
    func_02032c50(buf);
    result = func_020310c8(0);
    *(int *) (p5c + 4) = result;
    return result;
}
