/* func_ov050_02262734 @ 0x02262734, 0x64 bytes, Thumb, module ov050
 * mwccarm 1.2/base -O4,s
 */

extern int func_0209a000(unsigned short *, int);
extern void func_02094fd4(void *);
extern void func_0209a918(void *);
extern void func_0209ac50(void *, void *, unsigned short *);
extern void func_02068404(int, int, void *);
extern void func_02094fbc(void *);

struct Arg0 {
    char pad_00[0x40];
    int unk_40;
    char pad_44[140];
    int unk_D0;
};

typedef struct {
    int data[8];
} UnkStruct_02262734;

void func_ov050_02262734(struct Arg0 *arg0, void *arg1)
{
    unsigned short id[2];
    UnkStruct_02262734 local;
    id[0] = 0x1564;
    if (func_0209a000(id, 2)) {
        func_02094fd4(&local);
        func_0209a918(arg1);
        id[1] = 0x1564;
        func_0209ac50(arg1, &local, &id[1]);
        func_02068404(arg0->unk_40, 1, &local);
        arg0->unk_D0 = 0x2e;
        func_02094fbc(&local);
    } else {
        arg0->unk_D0 = 0x17;
    }
}
