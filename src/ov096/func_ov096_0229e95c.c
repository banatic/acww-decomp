/* func_ov096_0229e95c @ 0x0229e95c, 0x44 bytes, Thumb, module ov096
 * mwccarm 1.2/base -O4,s
 */

extern int func_ov096_0229f548(void *p);
extern int func_ov094_0229b8d8(void *p, int v);
extern void func_02066830(void *p, int v);
extern int func_ov094_0229b890(void *p, int v);

void func_ov096_0229e95c(void *obj)
{
    int val = func_ov096_0229f548(obj);
    ((char *) obj)[0xb1] = 1;
    func_02066830((char *) obj + 0x2e28, func_ov094_0229b8d8((char *) obj + 0xdb8, val));
    func_ov094_0229b890((char *) obj + 0xdb8, val);
}
