/* func_020ab278 @ 0x020ab278, 0x66 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020ab278 {
    int unk_00;
    char pad_04[28];
    int unk_20;
};

extern int func_020ab504(int);
extern int func_020ab0f4(struct UnkStruct_020ab278 *);
extern int func_020ab230(struct UnkStruct_020ab278 *);
extern int func_020a7e50(void);
extern int func_020ab0a4(struct UnkStruct_020ab278 *);
extern int func_020a7e44(void);
extern int func_020aaf20(struct UnkStruct_020ab278 *);
extern void func_020ab42c(int, int);

void func_020ab278(struct UnkStruct_020ab278 *self)
{
    if (self->unk_20 != 0 && func_020ab504(self->unk_20) < 0) {
        if (func_020ab0f4(self) != 0) {
            func_020ab230(self);
            return;
        } else {
            int flag = 0;
            if (func_020a7e50() != 0) {
                if (func_020ab0a4(self) != 0) {
                    flag = 1;
                }
            } else {
                if (func_020a7e44() != 0) {
                    if (func_020aaf20(self) != 0) {
                        flag = 1;
                    }
                }
            }
            if (flag != 0) {
                func_020ab42c(self->unk_20, self->unk_00);
            }
        }
    }
}
