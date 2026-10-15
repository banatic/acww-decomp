/* func_ov090_02298f20 @ 0x02298f20, 0x28 bytes, Thumb, module ov090
 * mwccarm 1.2/base -O4,s
 */

extern char data_ov090_02299820;
extern void *func_ov002_0220ba0c(void *);
extern void *func_ov002_0220826c(void *);

void *func_ov090_02298f20(void *obj)
{
    *(char **) obj = &data_ov090_02299820;
    func_ov002_0220ba0c((char *) obj + 0x1164);
    func_ov002_0220826c(obj);
    return obj;
}
