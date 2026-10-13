/* func_ov111_022a024c @ 0x022a024c, 0x30 bytes, Thumb, module ov111
 * mwccarm 1.2/base -O4,s
 */

extern unsigned short data_021fbe40;
extern void func_ov002_02208098(void *p, unsigned char c);
extern void func_ov111_0229efec(void *p);

void func_ov111_022a024c(void *param)
{
    if ((data_021fbe40 & 0x200) == 0) {
        unsigned char c = *(unsigned char *) ((char *) param + 0x98);
        func_ov002_02208098(param, c);
        func_ov111_0229efec(param);
    }
}
