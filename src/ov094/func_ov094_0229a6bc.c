/* func_ov094_0229a6bc @ 0x0229a6bc, 0xac bytes, Thumb, module ov094
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0xa50];
    unsigned int unk_A50;
    char pad_A54[5];
    unsigned char unk_A59;
    char pad_A5A[2];
    unsigned char unk_A5C;
} UnkStruct_0229a6bc;

extern char data_ov094_0229bf70[];
extern int func_02088d9c(void *);
extern int func_02088d94(void *);
extern int func_ov094_0229a50c(int);
extern void func_020896b8(int, void *, int, int, int, unsigned int, void *);
extern void func_ov094_0229a634(void *, int, int, int);
extern void func_ov094_0229a600(void *, int, int);

void func_ov094_0229a6bc(UnkStruct_0229a6bc *self, int b, int c)
{
    int loc[4];
    int p = b + func_02088d9c(data_ov094_0229bf70);
    int d = c + func_02088d94(data_ov094_0229bf70);
    int k = func_ov094_0229a50c(self->unk_A59);
    if (k != 0) {
        if (k == 0x1000) {
            func_020896b8(1, data_ov094_0229bf70, b, c, -1, self->unk_A50, 0);
        } else {
            loc[0] = k;
            loc[1] = 0;
            loc[2] = 0;
            loc[3] = k;
            func_020896b8(1, data_ov094_0229bf70, b, c, -1, self->unk_A50, loc);
        }
    }
    func_ov094_0229a634(self, p, d, -1);
    if (self->unk_A5C) {
        func_ov094_0229a600(self, p, d);
    }
}
