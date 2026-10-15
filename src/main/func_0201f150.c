/* func_0201f150 @ 0x0201f150, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    int unk_00;
    int unk_04;
} UnkStruct_0201f150;

extern unsigned short func_0201f520(unsigned short *, int);
extern void func_020157d4(void *, int (*)(unsigned short *, int), unsigned char, unsigned char);
extern int func_02015828(void *obj, int a);
extern void func_0202dbf0(void *obj, UnkStruct_0201f150 arg);
extern UnkStruct_0201f150 data_020d8e28;

#define Predicate_0201f520 ((int (*)(unsigned short *, int)) func_0201f520)

void func_0201f150(void *obj)
{
    func_020157d4(obj, Predicate_0201f520, 13, 1);
    func_02015828(obj, 0);
    func_0202dbf0(obj, data_020d8e28);
}
