/* func_ov123_0229c07c @ 0x0229c07c, 0x42 bytes, Thumb, module ov123
 * mwccarm 1.2/base -O4,s
 */

extern void func_ov002_02207e80(void *this, int a, int b, void *c);
extern void *func_ov002_02207f60(void *this);

void func_ov123_0229c07c(void *this)
{
    func_ov002_02207e80(this, 6, 0, *(void **) ((char *) this + 0x98));
    func_ov002_02207e80(this, 4, 0, *(void **) ((char *) this + 0x98));
    func_ov002_02207e80(this, 3, 0, *(void **) ((char *) this + 0x98));
    *(void **) ((char *) this + 0x94) = func_ov002_02207f60(this);
}
