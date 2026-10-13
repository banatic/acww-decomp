/* func_0208ed98 @ 0x0208ed98, 0x20 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a0c8(void *);
extern int func_0208a160(void *);

typedef struct {
    char pad_00[12];
    char unk_0C[20];
    int unk_20;
} UnkStruct_0208ed98;

void func_0208ed98(UnkStruct_0208ed98 *p)
{
    func_0208a0c8(p->unk_0C);
    if (func_0208a160(p->unk_0C)) {
        p->unk_20 = 2;
    }
}
