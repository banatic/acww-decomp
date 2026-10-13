/* func_02072e64 @ 0x02072e64, 0x2c bytes, Thumb, module main
 * mwccarm 1.2/base -O4,s
 */

extern void func_02062e50(void *);
extern void func_020a87e0(void *, void *);
extern void func_02072e50(void *, void *);
extern void func_02062e00(void *);

void func_02072e64(void *param1, void *param2)
{
    void *sp_buffer[9]; // 0x24 bytes

    func_02062e50(sp_buffer);
    func_020a87e0(sp_buffer, param2);
    func_02072e50(param1, sp_buffer);
    func_02062e00(sp_buffer);
}
