/* func_ov003_02218dcc @ 0x02218dcc, 0x30 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_02010f5c(void *);

typedef struct {
    char pad_00[2];
    unsigned char flag;
} SubA;

void func_ov003_02218dcc(void *r0)
{
    SubA *sub = (SubA *) ((char *) r0 + 0x7d4);
    if (sub->flag == 0) {
        if (*(int *) ((char *) r0 + 0x818) == 2) {
            sub->flag = 2;
        } else if (*(int *) ((char *) r0 + 0x818) == 1) {
            sub->flag = 1;
        }
    }
    func_02010f5c(r0);
}
