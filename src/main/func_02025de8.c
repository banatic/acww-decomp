/* func_02025de8 @ 0x02025de8, 0x88 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct SubB {
    char pad_00[0x830];
    int unk_830;
} SubB;

typedef struct UnkStruct_02025de8 {
    char pad_00[0x100];
    SubB *unk_100;
    char pad_104[0x20];
    char buf_124[0x40];
    int *unk_164;
} UnkStruct_02025de8;

extern int func_0209b91c(int *);
extern int func_0209bd44(void *);
extern int func_0202d9c4(UnkStruct_02025de8 *);
extern int func_0209bc40(int);
extern void func_0209b9cc(int *, int, char *, int, int);
extern void func_020784f8(int, int, char *, int, int);
extern int func_0207f270(int);
extern int func_020794d0(int);
extern void func_0209bd5c(int);

void func_02025de8(UnkStruct_02025de8 *p)
{
    int r4, r7, r6;
    r6 = p->unk_100->unk_830;
    r4 = 0;
    if (func_0209bd44((void *) func_0209b91c(p->unk_164)) == 0) {
        r7 = func_0209bc40(func_0202d9c4(p));
        r4 = 1;
    } else {
        r7 = func_0209bc40(func_0209b91c(p->unk_164));
    }
    func_0209b9cc(p->unk_164, r7, p->buf_124, 0, r4);
    func_020784f8(r6, r7, p->buf_124, 4, r4);
    func_0209bd5c(func_020794d0(func_0207f270(r6)));
}
