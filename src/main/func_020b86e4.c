/* func_020b86e4 @ 0x020b86e4, 0x58 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned char pad_00[0x108];
    int unk_108;
    unsigned char pad_10C;
    unsigned char flag;
} UnkStruct_020b86e4;

extern int func_0208a844(void *arg);
extern void func_020b884c(void *arg);
extern int func_020b8854(void *arg);
extern int func_020b8878(void *arg);
extern void *func_0208a9ac(void *arg);

void func_020b86e4(void *p)
{
    UnkStruct_020b86e4 *s = (UnkStruct_020b86e4 *) p;

    if (s->unk_108 > 0) {
        s->unk_108--;
    }

    if (func_0208a844((char *) p + 8) == 0) {
        func_020b884c(p);
        return;
    }

    if (func_020b8854(p) != 0) {
        goto final;
    }

    if (func_020b8878(p) != 0) {
        if (s->flag == 0) {
            return;
        }
    }

final:
    p = (char *) p + 8;
    func_0208a9ac(p);
}
