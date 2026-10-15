/* func_0208be44 @ 0x0208be44, 0x40 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    char pad_00[0x24];
    unsigned char unk_24;
} UnkStruct_0208be44;
extern int func_020a7e50(void);
extern int func_020a7ffc(void);
extern void func_020a7e64(void);
extern int func_020a7e44(void);
extern int func_020a812c(void);
extern void func_020a7e70(void);
extern void func_020a7dec(void);

void func_0208be44(UnkStruct_0208be44 *s)
{
    if (s->unk_24 == 0) {
        return;
    }
    if (func_020a7e50()) {
        if (func_020a7ffc()) {
            func_020a7e64();
        }
    } else {
        if (func_020a7e44()) {
            if (func_020a812c()) {
                func_020a7e70();
            }
        }
    }
    func_020a7dec();
}
