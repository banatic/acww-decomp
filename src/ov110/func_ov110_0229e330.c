/* func_ov110_0229e330 @ 0x0229e330, 0x38 bytes, Thumb, module ov110
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov110_0229d5f0(void *);
extern void func_ov110_0229c574(void *);
extern void func_ov094_0229a084(void *);
extern void func_ov094_0229af20(void *);
extern void func_ov094_0229bbc0(void *);

void func_ov110_0229e330(void *self)
{
    func_ov110_0229d5f0(self);
    func_ov094_0229a084((char *) self + 0xbc0);
    func_ov094_0229af20((char *) self + 0x138);
    func_ov094_0229bbc0((char *) self + 0xb98);
    func_ov110_0229c574(self);
}
