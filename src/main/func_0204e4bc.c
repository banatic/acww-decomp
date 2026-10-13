/* func_0204e4bc @ 0x0204e4bc, 0x54 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x28];
} UnkStruct_0204e4bc;
typedef struct {
    UnkStruct_0204e4bc *unk_00;
    int unk_04;
    int unk_08;
} UnkStruct_0204e4bc_2;
extern int data_021e9aac;
extern unsigned char *func_0204e724(int *);
extern void func_02037e88(UnkStruct_0204e4bc *, unsigned char);

void func_0204e4bc(UnkStruct_0204e4bc_2 *self)
{
    unsigned char *q;
    UnkStruct_0204e4bc *p;
    int j = 0;
    int k;
    int i = 0;

    q = func_0204e724(&data_021e9aac);
    if (q != 0) {
        p = self->unk_00;
        for (i = 0; i < self->unk_08; i++) {
            for (k = j; k < self->unk_04; k++) {
                if (p != 0) {
                    func_02037e88(p, *q);
                }
                p++;
                q++;
            }
        }
    }
}
