/* func_02069128 @ 0x02069128, 0x3e bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a448(char *p, int arg);
extern void func_0208fd88(char *p);
extern void func_0208a2b0(char *p);
extern void func_0208fc04(char *p);

typedef struct UnkStruct_02069128 {
    int a;
    int b;
    int c;
    char subA[0x44];
    char subB[0x24];
    int unk_74;
    int g;
    int h;
} UnkStruct_02069128;

UnkStruct_02069128 *func_02069128(UnkStruct_02069128 *p)
{
    p->a = 0;
    p->b = 0;
    p->c = 0;
    func_0208a448(p->subA, 1);
    func_0208fd88(p->subB);
    p->unk_74 = 0;
    p->g = 0;
    p->h = 0;
    func_0208a2b0(p->subA);
    func_0208fc04(p->subB);
    return p;
}
