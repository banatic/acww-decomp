/* res_rows_open: 6 functions, module ov139
 * mwccarm 1.2/base -O4,s
 * func_ov139_02299b54 @ 0x02299b54, 0x3c bytes, Thumb
 * func_ov139_02299b30 @ 0x02299b30, 0x24 bytes, Thumb
 * func_ov139_02299af8 @ 0x02299af8, 0x38 bytes, Thumb
 * func_ov139_02299adc @ 0x02299adc, 0x1c bytes, Thumb
 * func_ov139_02299ac0 @ 0x02299ac0, 0x1c bytes, Thumb
 * func_ov139_02299a80 @ 0x02299a80, 0x40 bytes, Thumb
 */

typedef struct {
    char pad_00[0x9a0];
    unsigned short unk_9A0;
    unsigned char unk_9A2;
} UnkStruct_02299af8;

struct UnkStruct_02299a80 {
    char pad_00[0x93c];
    char unk_93C;
    char pad_93D[0x980 - 0x93c - 1];
    char unk_980;
    char pad_981[0x9a2 - 0x980 - 1];
    unsigned char unk_9A2;
};

extern void *func_ov002_0220b10c(void *p);
extern void __cxa_vec_ctor(void *data, int a, int b, void (*callback3)(void *), void (*callback4)(void *));
extern void *func_020b9cfc(void *p);
extern int **func_02070be8(void *element);
extern void *func_02070c08(void *element);
extern void __cxa_vec_cleanup(void *, int, int, void (*callback3)(void *));
extern void *func_ov002_0220b0f4(void *);
extern void func_ov002_0220b04c(void *self);
extern void func_ov002_0220b06c(void *self, int arg2, unsigned int a, unsigned int b);
extern void func_0208aa70(void *self);
extern void func_ov139_02299770(void *);
extern void func_020b9ccc(void *);
extern int func_ov139_022995c0(void *ptr, int n);
extern int func_020b9b6c(void *ptr0, void *ptr1, unsigned char byte, int n);
extern void func_ov139_022995a0(void *ptr, int n);

#define DisposeElement_func_02070c08 ((void (*)(void *)) func_02070c08)

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov139_02299b54(void *p)
{
    func_ov002_0220b10c(p);
    __cxa_vec_ctor((char *) p + 0xcc, 0x14, 0x6c, DisposeElement_func_02070c08, DisposeElement_func_02070be8);
    func_020b9cfc((char *) p + 0x93c);
    return p;
}

#undef DisposeElement_func_02070c08
#undef DisposeElement_func_02070be8

#define DisposeElement_func_02070be8 ((void (*)(void *)) func_02070be8)

void *func_ov139_02299b30(void *p)
{
    __cxa_vec_cleanup((char *) p + 0xCC, 0x14, 0x6C, DisposeElement_func_02070be8);
    func_ov002_0220b0f4(p);
    return p;
}

#undef DisposeElement_func_02070be8

void func_ov139_02299af8(UnkStruct_02299af8 *self, unsigned char value, int arg2)
{
    self->unk_9A2 = value;
    self->unk_9A0 = 0;
    func_ov002_0220b04c(self);
    func_ov002_0220b06c(self, arg2, 0x90, 0x18);
    func_0208aa70(self);
}

void func_ov139_02299adc(void *self)
{
    func_ov139_02299770(self);
    func_020b9ccc((char *) self + 0x93c);
}

void func_ov139_02299ac0(void *ptr)
{
    func_ov139_02299770(ptr);
    func_020b9ccc((char *) ptr + 0x93c);
}

void func_ov139_02299a80(struct UnkStruct_02299a80 *self)
{
    if (func_ov139_022995c0(self, 1) != 0) {
        if (func_020b9b6c(&self->unk_93C, &self->unk_980, self->unk_9A2, 7) != 0) {
            func_ov139_022995a0(self, 1);
        }
    }
}
