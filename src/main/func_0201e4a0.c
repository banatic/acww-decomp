/* func_0201e4a0 @ 0x0201e4a0, 0x34 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

typedef struct {
    unsigned int unk_00;
    unsigned char unk_04;
} ResultStruct;

extern int func_02021118(void *p);
extern int func_02022034(void *p);
extern void func_0202dac0(void *p);

void func_0201e4a0(void *p, ResultStruct *r)
{
    func_02021118(p);
    func_02022034(p);
    r->unk_00 = (unsigned int) p + 0x104;
    r->unk_04 = ((unsigned char *) p)[0x122];
    func_0202dac0(p);
}
