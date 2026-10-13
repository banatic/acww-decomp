/* func_02065c98 @ 0x02065c98, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020de770[];
extern void func_020a887c(void *);

void *func_02065c98(void *obj)
{
    *(void **) obj = data_020de770;
    func_020a887c(obj);
    return obj;
}
