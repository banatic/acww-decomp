/* func_0207adf4 @ 0x0207adf4, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x64];
    int unk_64;
} GlobalType;

typedef struct {
    char data[0x7ec];
} Entry;

extern GlobalType *data_020ccf94;
extern int func_02073dd4(GlobalType *g, int val);
extern unsigned int func_0208150c(Entry *e);
extern int func_02003704(void *);
extern void func_0207d148(Entry *e);

void func_0207adf4(Entry *p)
{
    int i;

    if (func_02073dd4(data_020ccf94, data_020ccf94->unk_64) != 0) {
        return;
    }

    for (i = 0; i < 8; i++) {
        if (func_02003704((void *) func_0208150c(p)) != 0) {
            func_0207d148(p);
        }
        p++;
    }
}
