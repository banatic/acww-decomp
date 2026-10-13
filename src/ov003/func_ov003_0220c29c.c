/* func_ov003_0220c29c @ 0x0220c29c, 0x38 bytes, Thumb, module ov003
 * mwccarm 1.2/base -O4,s
 */

extern void func_0203f130(void *);
extern void func_02066a30(void *);
extern void func_020b7f70(void *);
extern char data_ov003_02238010[];
extern char data_ov003_02238078[];

void *func_ov003_0220c29c(void *this)
{
    func_0203f130(this);
    func_02066a30((char *) this + 0xec);
    *(void **) this = (void *) data_ov003_02238010;
    *(void **) ((char *) this + 0xec) = (void *) data_ov003_02238078;
    func_020b7f70((char *) this + 0x138);
    return this;
}
