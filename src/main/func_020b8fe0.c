/* func_020b8fe0 @ 0x020b8fe0, 0x50 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_0208a840(void);
extern int func_0208a1cc(void);
extern void func_0208a1f0(void *dst, const void *src);
extern void func_0208a1ec(void *dst, int a);
extern void func_0208a1e8(void *dst, int a);
extern void func_0208a1e0(void *dst, int a, int b);
extern void func_0208a0c8(void *dst);
extern char data_020d71d4[];

typedef struct {
    char pad_00[0xcc];
    int unk_CC;
} UnkStruct_020b8fe0;

void func_020b8fe0(UnkStruct_020b8fe0 *self)
{
    int v;

    func_0208a840();
    v = func_0208a1cc();
    func_0208a1f0(&self->unk_CC, data_020d71d4);
    func_0208a1ec(&self->unk_CC, 1);
    func_0208a1e8(&self->unk_CC, 0);
    func_0208a1e0(&self->unk_CC, v, 0);
    func_0208a0c8(&self->unk_CC);
}
