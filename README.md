# TALX 9110

This repository archives the source code for the TALX screen
reader for the Nokia 9110 Communicator smartphone.
It was developed by Marcus Groeber and Torsten Brand in
2001, and to my (mg's) knowledge was the first
available screen reader for mobile phones.

It served as the proof-of-concept for the TALKS 9210
screen reader for Symbian that we later updated for
Series 60, over time adding support for screen
magnification and touch screens, before Nokia stopped
production of Symbian phones in 2011.

TALX included a number of unusual technical features:

  * Text-to-speech output by using pre-synthesized word
    recordings.
     * Recordings were compressed using the built-in
       RT24 codec (2400 bps) because this was the only
       way for outputting audio on the Communicator.
     * Unknown words would be spelled letter-by-letter
  * Support for a full-featured external speech synthesizer,
    attached via the serial port.
  * Built-in drivers for Braille displays (also via
    serial port).

I am planning to add some more in-depth documentation
to this repository over time. For now, you can find a
snapshot of the original web page at
https://web.archive.org/web/20020206063258/http://www.talx.de/index_e.htm.