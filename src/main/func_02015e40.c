/* func_02015e40 @ 0x02015e40, 0x30 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02094fd4(void *);
extern void func_02095074(void *, void *);
extern void func_02068404(void *, void *, void *);
extern void func_02094fbc(void *);

typedef struct {
    unsigned char pad_00[0x40];
    void *unk_40;
} UnkStruct_02015e40;

typedef struct {
    unsigned char data[0x20];
} UnkStruct_02015e40_2;

void func_02015e40(UnkStruct_02015e40 *a, void *b, void *c)
{
    UnkStruct_02015e40_2 local;

    func_02094fd4(&local);
    func_02095074(b, &local);
    func_02068404(a->unk_40, c, &local);
    func_02094fbc(&local);
}
