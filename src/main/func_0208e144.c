/* func_0208e144 @ 0x0208e144, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a1f0(void *a, void *b);
extern void func_0208a1ec(void *a, int b);
extern void func_0208a1e8(void *a, int b);

typedef struct {
    char data[8];
} DataElem;
extern DataElem data_020d5b3c[];

typedef struct {
    char pad_00[0x10];
    int unk_10;
    char unk_14;
} UnkStruct_0208e144;

void func_0208e144(UnkStruct_0208e144 *p)
{
    func_0208a1f0(&p->unk_14, &data_020d5b3c[p->unk_10]);
    func_0208a1ec(&p->unk_14, 1);
    func_0208a1e8(&p->unk_14, 0);
}
