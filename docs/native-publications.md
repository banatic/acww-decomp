# Audited Native publication stores

HBlank samples the sky's RAM while the frame producer is running. Moving all
Native work to the next call boundary can delay a selector change past those
reads, even when both completed buffers and the frame-end RAM agree.

There are three independent selectors covered by this boundary:

| Owner | Store PC | Destination | Published state |
| --- | --- | --- | --- |
| `func_020ba340` | `020ba348` | `021f8acc` | The line-shift slot sampled by HBlank |
| `func_020bae60` | `020bb040` | `021f75b4` | The set of cloud tables shown |
| `func_020bb090` | `020bb16e` | `021f6f70` | The completed gradient buffer |

The distinction matters in `villager-talk`. At frame 4160, line 20, the ROM's
HBlank handler reads shift slot 0, containing 13. Delaying that selector until
after the gradient calculation leaves slot 1, containing 9, visible instead.
The handler consequently reads gradient entry 29 instead of 33. The gradient
buffers themselves, their selector and their publication time can all agree
while the displayed colours differ.

`tools/native_publish.py` checks the complete original source and ROM body for
each supported store. It compiles PC copies that pass the body's computed
selector and actual destination to `native_publish_word`. The corresponding
Clean copies of `Sky_SwapLineShift` and `Sky_UpdateGradient` use the same
boundary. Original files in `src/` and `clean/` are unchanged.

During Reference recording, the interpreter observes the audited word store
after the RAM write and before counting its instruction. It records a
publication only when that owner is selected for Native and the current
crossing frame represents Native execution. Initialization stores and a
Reference-only owner do not generate these events.

During replay, the helper checks the stream's next event, store PC,
destination, width and computed value. It waits until the recorded store time
with IRQ delivery and thread switching enabled. It writes the Native-computed
value; the recorded value is only a check. Work after the store resumes at
the next crossing's time, as other Native continuations do.

A nested interpreter return can leave a completed instruction slice pending.
`run_native_store_boundary` finishes that slice before the Native store, while
preserving the deadline of an open partial slice. A store that arrives after
hardware time has already advanced past it is rejected: rewinding the CPU's
step counter cannot undo a displayed line.

This is an explicit list of audited stores, not a timing model for arbitrary
RAM writes. Other observable stores need their own source and ROM audit.
`func_020bae60` fills the set of cloud tables not shown, then shows it. Native, the
selector changed at the call's start: the new-game recording showed the new set early
in frames 7475, 7481, 7584, 7591, 7600 and 7692 (memory equal at every checkpoint).
Published at the ROM's store, the frames agree, and the function runs as Native.

Run `python tools/test_native_publish.py` for the boundary tests. They compile
both actual Native copies, execute both ARM store instructions through the
recorder, and cover regular and DMA-sized slice deadlines, nested returns,
an IRQ during a wait, and an IRQ between the two publications. Negative cases
reject bad values, event identity, ordering, width, missing events and late
arrival. Controls with the former slice ordering and a delayed line-shift
selector must fail. Scene and recording gates are still required in addition
to these boundary tests.
