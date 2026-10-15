/* func_ov004_02228100 @ 0x02228100, 0x64 bytes, Thumb, module ov004
 * mwccarm 1.2/base -O4,s
 */

extern unsigned int func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_ov004_02228164(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern int func_0200e91c(void *);

typedef struct UnkStruct_02228100 {
    unsigned char pad_00[0x820];
    unsigned short unk_820;
    unsigned short unk_822;
} UnkStruct_02228100;

typedef struct UnkStruct_02228100_2 {
    int data[3];
} UnkStruct_02228100_2;

typedef struct UnkStruct_02228100_3 {
    int data[4];
} UnkStruct_02228100_3;

int func_ov004_02228100(UnkStruct_02228100 *p0, unsigned short *p1, int p2, int p3, int p4, int p5, int p6, short p7)
{
    UnkStruct_02228100_2 s;
    UnkStruct_02228100_3 t;
    int result;

    func_0200e92c(&s);
    func_0200e90c(&s, 0x36, p6, p7);

    p0->unk_822 = *p1;
    p0->unk_820 = p0->unk_822;

    func_ov004_02228164(&t, p2, p3, p4, p5);
    result = func_0200e894(p0, &s);
    func_0200e91c(&s);

    return result;
}
