/* func_020f2bcc @ 0x020f2bcc, 0x24 bytes, ARM, module autoload_2
 * mwccarm 1.2/base -O4,s
 */

struct UnkStruct_020f2bcc {
    void *v;
};
extern void func_020f4514(void *);
extern char data_0213edac;

void *func_020f2bcc(void *p)
{
    ((struct UnkStruct_020f2bcc *) p)->v = &data_0213edac;
    func_020f4514(p);
    return p;
}
