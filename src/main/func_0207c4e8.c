/* func_0207c4e8 @ 0x0207c4e8, 0xb0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x4050];
    long long unk_4050;
    long long unk_4058;
    char unk_4060[1];
} UnkStruct_0207c4e8;

extern char data_021d1554[];

extern int func_0207c5e4(UnkStruct_0207c4e8 *self, void *);
extern int func_0207cd40(UnkStruct_0207c4e8 *self);
extern void *func_0207cec0(UnkStruct_0207c4e8 *self, int t);
extern void func_02081660(void *p);
extern void func_0207c9b8(char *p, UnkStruct_0207c4e8 *self);
extern int func_0207c598(UnkStruct_0207c4e8 *self);
extern void func_02081518(char *g, int id, int a, int b, int c);
extern void func_0207c3b0(UnkStruct_0207c4e8 *self, void *o, int t, char *g, int one, void *a1);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int n);

void func_0207c4e8(UnkStruct_0207c4e8 *self, void *a1)
{
    int t;
    void *o;
    int id;

    if (func_0207c5e4(self, a1) == 0) {
        return;
    }
    t = func_0207cd40(self);
    o = func_0207cec0(self, t);
    if (o != 0) {
        func_02081660(o);
        func_0207c9b8(self->unk_4060, self);
        id = func_0207c598(self);
        if (id != -1) {
            func_02081660(data_021d1554);
            func_02081518(data_021d1554, (unsigned char) id, 1, 0, 0);
            func_0207c3b0(self, o, t, data_021d1554, 1, a1);
        }
    }
    MI_CpuCopy8(a1, &self->unk_4050, 8);
    if (self->unk_4058 != 0) {
        MI_CpuCopy8(a1, &self->unk_4058, 8);
    }
}
