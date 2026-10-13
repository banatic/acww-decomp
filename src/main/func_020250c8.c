/* func_020250c8 @ 0x020250c8, 0x80 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct Entry Entry;
struct Entry {
    unsigned char pad_00[0x830];
    void *unk_830;
};

typedef struct UnkStruct_020250c8 {
    unsigned char pad_00[0x100];
    Entry *unk_100;
    unsigned char pad_104[0x20];
    char unk_124[0x40];
    void *unk_164;
} UnkStruct_020250c8;

extern int func_0202d9c4(void *p);
extern int func_0209bc40(int x);
extern int func_0204bcdc(void *p);
extern int func_02080834(void *a, void *b);
extern int func_0209b69c(void *a, unsigned char b);
extern void func_0207860c(void *a, unsigned char b);
extern void func_0209bb90(int a, int b);
extern void func_02078648(void *a, int b);
extern int func_0207f270(void *a);
extern void func_02079478(int a);

void func_020250c8(UnkStruct_020250c8 *p)
{
    void *entry;

    entry = p->unk_100->unk_830;

    if (func_0209bc40(func_0202d9c4(p)) == 4) {
        if (func_0204bcdc(&p->unk_124) != 0) {
            func_0207860c(entry, (unsigned char) func_0209b69c(p->unk_164, (unsigned char) func_02080834(entry, &p->unk_124)));
        }
    }

    func_0209bb90(func_0202d9c4(p), 1);
    func_02078648(entry, 1);
    func_02079478(func_0207f270(entry));
}
