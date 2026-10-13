/* func_020b10b8 @ 0x020b10b8, 0x78 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x2a];
    unsigned short arr[16];
} WorkStruct;
extern WorkStruct data_021ee418;
extern int func_02090158(WorkStruct *);
extern WorkStruct *func_020900e4(WorkStruct *);
extern void func_020b1a24(WorkStruct *);
extern int func_020b11a4(WorkStruct *);
void func_020b10b8(void)
{
    WorkStruct *self = &data_021ee418;
    int i;
    int j;
    int found;
    if (!func_02090158(self)) {
        return;
    }
    self = func_020900e4(self);
    found = 0;
    for (i = 0; i < 16; i++) {
        if (self->arr[i] == 0xFFFF) {
            continue;
        }
        found++;
        for (j = 0; j < i; j++) {
            if (self->arr[i] == self->arr[j]) {
                func_020b1a24(self);
                return;
            }
        }
    }

    if (found != 0) {
        if (func_020b11a4(self)) {
            func_020b1a24(self);
        }
    }
}
