/* func_02089bbc @ 0x02089bbc, 0x18 bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern char data_020e2044;
extern void func_02089c58(void *);

void *func_02089bbc(void *obj)
{
    *(void **) obj = (void *) &data_020e2044;
    func_02089c58(obj);
    return obj;
}
