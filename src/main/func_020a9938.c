/* func_020a9938 @ 0x020a9938, 0xa0 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_020a98e4(void *);
extern int func_020a982c(void *);
extern int func_020a9754(void *);
extern int func_020a9708(void *);
extern int func_020a958c(void *);
extern int func_020a967c(void *);
extern int func_020a9540(void *);

typedef struct {
    unsigned char pad_00[4];
    unsigned char unk_04;
    unsigned char pad_05[0x88];
    unsigned char unk_8D;
} UnkStruct_020a9938;

int func_020a9938(UnkStruct_020a9938 *self, const unsigned char *msg)
{
    int flag = 1;

    func_020a98e4(self);
    self->unk_8D = *msg;

    flag = (flag & func_020a982c(self)) != 0;
    if (flag) {
        flag = (flag & func_020a9754(self)) != 0;
    }
    if (flag) {
        flag = (flag & func_020a9708(self)) != 0;
    }
    if (flag) {
        if (self->unk_04 != 0) {
            flag = (flag & func_020a958c(self)) != 0;
        } else {
            flag = (flag & func_020a967c(self)) != 0;
        }
    }
    if (flag) {
        flag = (flag & func_020a9540(self)) != 0;
    }
    return flag;
}
