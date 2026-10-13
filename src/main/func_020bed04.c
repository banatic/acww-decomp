/* func_020bed04 @ 0x020bed04, 0x60 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[8];
    unsigned short unk_08;
    unsigned short arr1[15];
    unsigned short arr2[16];
} UnkStruct_020bed04;

extern unsigned char data_020d2324[];
extern int func_020bec40(UnkStruct_020bed04 *, int);

int func_020bed04(UnkStruct_020bed04 *self, int param2)
{
    int found = 0;
    if (self->unk_08) {
        int i = 0;
        int zero = 0;
        for (; i < 15; i++) {
            int ret = func_020bec40(self, i);
            unsigned char b = data_020d2324[i];
            int cond = (((b >> 4) & 0xf) == param2) ? 1 : zero;
            if (ret && cond) {
                self->arr2[b & 0xf] = self->arr1[i];
                found = 1;
            }
        }
    }
    return found;
}
