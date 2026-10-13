/* func_ov051_02260608 @ 0x02260608, 0x78 bytes, Thumb, module ov051
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x40];
    int unk_40;
    unsigned char pad_44[0x6c];
    int *unk_B0;
} UnkStruct_02260608;

extern int func_020a12d4(UnkStruct_02260608 *self, int idx);
extern int func_ov051_022605e8(UnkStruct_02260608 *self, unsigned char val);
extern void func_020984e8(void);
extern void func_02099870(void);
extern int func_020950c0(void);
extern void func_0206844c(int a, char *b, int c);
extern unsigned char data_ov051_022614bc[];
extern int data_ov051_022615c0;

void func_ov051_02260608(UnkStruct_02260608 *self, int idx)
{
    char local;
    int result;

    if (func_020a12d4(self, idx)) {
        result = func_ov051_022605e8(self, data_ov051_022614bc[idx]);
    } else if (idx == 0) {
        func_020984e8();
        func_02099870();
        if (func_020950c0() == 0) {
            result = 0x21;
        } else {
            result = 0x2f;
        }
    } else {
        result = func_ov051_022605e8(self, 0x23);
    }

    local = (char) result;
    func_0206844c(self->unk_40, &local, data_ov051_022615c0);

    if (idx == 1) {
        int *ptr = self->unk_B0;
        (*(int *) ((char *) ptr + 0x714))++;
    }
}
