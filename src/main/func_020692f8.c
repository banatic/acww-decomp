/* func_020692f8 @ 0x020692f8, 0x84 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a873c(void *a, void *b);
extern int func_02050bf8(unsigned char c);
extern int func_02050c04(unsigned char c);
extern void func_020a9334(void *self, int value);

typedef struct {
    char pad_00[0x24];
    void *unk_24;
    char pad_28[0x10];
    char unk_38;
} UnkStruct_020692f8;

void func_020692f8(UnkStruct_020692f8 *self)
{
    unsigned char local;
    char *base;
    int first;
    int second;
    int rem;
    int result;

    func_020a873c((char *) self + 0x38, &local);
    local--;
    base = (char *) self->unk_24;
    first = *(int *) (base + 0x1a60);
    second = *(int *) (base + 0x1a5c);
    if (second == 0) {
        goto simple;
    }
    rem = (second - 0xac00) % 0x1c;
    if (rem == 0) {
        goto simple;
    }
    if (first != 1) {
        goto f2b;
    }
    if (local != 6) {
        goto f2a;
    }
    if (rem != 8) {
        goto f2a;
    }
    result = func_02050bf8(local);
    goto done;
f2a:
    result = func_02050c04(local);
    goto done;
f2b:
    result = func_02050c04(local);
    goto done;
simple:
    result = func_02050bf8(local);
    goto done;
done:
    func_020a9334(self, result);
}
