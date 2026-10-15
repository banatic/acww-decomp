/* func_0201bd48 @ 0x0201bd48, 0x6c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern int func_020a7278(void);
extern int func_0201c45c(void *self);
extern void func_0201c0c8(void *self, int a, int b, int c);
extern void func_0201aff4(void *addr, int value);
extern int func_0208239c(void *addr);

typedef struct UnkStruct_0201bd48 {
    char pad_00[0x64];
    int unk_64;
} UnkStruct_0201bd48;
extern UnkStruct_0201bd48 *data_020ccf94;

int func_0201bd48(void *self)
{
    if (func_020a7278() != 0) {
        func_0201c0c8(self, 1, data_020ccf94->unk_64, 4);
    }
    if (func_0201c45c(self) == 0) {
        return 0;
    }
    *((int *) ((char *) self + 0xa0)) = -5120;
    *((int *) ((char *) self + 0x9c)) = 0;
    func_0201aff4((char *) self + 0x350, *((short *) ((char *) self + 0x8e)));
    ((unsigned char *) self)[0x447] = (unsigned char) func_0208239c((char *) self + 0xea);
    return 1;
}
