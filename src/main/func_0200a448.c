/* func_0200a448 @ 0x0200a448, 0x64 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0200e92c(void *);
extern void func_0200e90c(void *, int, int, short);
extern void func_0200a4ac(void *, int, int, int, int);
extern int func_0200e894(void *, void *);
extern void func_0200e91c(void *);

typedef struct UnkStruct_0200a448 {
    unsigned char pad_00[0x820];
    unsigned short unk_820;
    unsigned short unk_822;
} UnkStruct_0200a448;

typedef struct UnkStruct_0200a448_2 {
    int data[3];
} UnkStruct_0200a448_2;

typedef struct UnkStruct_0200a448_3 {
    int data[4];
} UnkStruct_0200a448_3;

int func_0200a448(UnkStruct_0200a448 *p0, unsigned short *p1, int p2, int p3, int p4, int p5, int p6, short p7)
{
    UnkStruct_0200a448_2 s;
    UnkStruct_0200a448_3 t;
    int result;

    func_0200e92c(&s);
    func_0200e90c(&s, 0x30, p6, p7);

    p0->unk_822 = *p1;
    p0->unk_820 = p0->unk_822;

    func_0200a4ac(&t, p2, p3, p4, p5);
    result = func_0200e894(p0, &s);
    func_0200e91c(&s);

    return result;
}
