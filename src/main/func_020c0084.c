/* func_020c0084 @ 0x020c0084, 0x74 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x4c];
    int unk_4C;
    int unk_50;
    char pad_54[0xc];
    unsigned int unk_60;
} UnkStruct_020c0084;

extern int data_020d274c[];
extern int data_020d2444[];
extern int data_020d27fc[];
extern int data_020d2468[];
extern int func_0208a1cc(void *p);

void func_020c0084(UnkStruct_020c0084 *self, int n)
{
    int lim;
    int *tbl;
    int a;
    unsigned int v;
    int val;

    v = self->unk_60;
    a = ((v >> 30) & 1) ? 1 : 0;
    if (((v >> 31) & 1) != 0) {
        if (a != 0) {
            tbl = data_020d274c;
            lim = 0xb0;
        } else {
            tbl = data_020d2444;
            lim = 0x24;
        }
    } else {
        if (a != 0) {
            tbl = data_020d27fc;
            lim = 0xb0;
        } else {
            tbl = data_020d2468;
            lim = 0x24;
        }
    }
    if (n < 0) {
        n = func_0208a1cc((char *) self + 0x10);
    }
    if (n < 0) {
        lim = 0;
    } else if (n <= lim) {
        lim = n;
    }
    val = tbl[lim];
    self->unk_4C = val;
    self->unk_50 = val;
}
