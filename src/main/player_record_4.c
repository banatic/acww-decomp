/* player_record_4: 5 functions, module main
 * mwccarm 1.2/base -O4,s
 * func_02099e58 @ 0x02099e58, 0x20 bytes, Thumb
 * func_02099e40 @ 0x02099e40, 0x18 bytes, Thumb
 * func_02099e18 @ 0x02099e18, 0x28 bytes, Thumb
 * func_02099df4 @ 0x02099df4, 0x24 bytes, Thumb
 * func_02099dcc @ 0x02099dcc, 0x28 bytes, Thumb
 */

struct UnkStruct_02099e58 {
    char pad_00[30];
    unsigned short unk_1E;
};

typedef struct {
    char pad_00[0xe];
    char unk_0E;
    char pad_0F[0x1e - 0xe - 1];
    unsigned short unk_1E;
    char unk_20;
} UnkStruct_02099e18;

extern void func_020642fc(void *object);
extern int func_02003780(void *);
extern int func_02003750(void *ptr);
extern void func_020642f8(void *ptr);
extern void func_020642e0(void *);
extern void func_02003738(void *);
extern int func_02064294(void *);
extern int func_02003704(void *);
extern void func_020642d0(unsigned int a, unsigned int b);
extern void func_02003728(void *a, void *b);

struct UnkStruct_02099e58 *func_02099e58(struct UnkStruct_02099e58 *ptr)
{
    func_020642fc(ptr);
    func_02003780((char *) ptr + 14);
    ptr->unk_1E = 0xfff1;
    return ptr;
}

void *func_02099e40(void *ptr)
{
    func_02003750((char *) ptr + 0xe);
    func_020642f8(ptr);
    return ptr;
}

void func_02099e18(UnkStruct_02099e18 *s)
{
    func_020642e0(s);
    func_02003738(&s->unk_0E);
    s->unk_1E = 0xfff1;
    s->unk_20 = -128;
}

int func_02099df4(void *arg)
{
    if (func_02064294(arg) && func_02003704((char *) arg + 0xe)) {
        return 1;
    }
    return 0;
}

void func_02099dcc(char *a, void *b, char c, int d, unsigned short *e)
{
    func_020642d0((unsigned int) a, (unsigned int) d);
    func_02003728(a + 0xe, b);
    *(unsigned short *) (a + 0x1e) = *e;
    a[0x20] = c;
}
