This is an automatic translation, may be incorrect in some places. See sources and examples!

# Gyverbeeper
Pisk generation by timer
- in simple words: the library allows the asynchronously pitch zummer several times
- Asynchronous work
- software asynchronous squeak based on Micros () or Tone () by choice
- installation of active and passive time
- Built -in PGM table for 90 notes (from to control to the mi fifth octave)

## compatibility
All arduino

## Content
- [installation] (# Install)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- For work, a library is required [gyverblinker] (https://github.com/gyverlibs/gyverblinker)
- The library can be found by the name ** gyverbeeper ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download the library] (https://github.com/gyverlibs/gyverbeeper/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!

<a id="usage"> </a>

## Usage
`` `CPP
// Designer
BLINker ();
Blinker (Uint8_T PIN);

// Methods
// squealing with the specified period (ISS, or note with the prefix US_)
VOID beepus (uint16_t us);

// To squeak with the US period (ISS, or note with the prefix US_) amount time, active High time, Low silence
VOID BEEPUS (UINT16_T US, UINT16_T AMOUNT, UINT16_T HIGH, UINT16_T LOW = 0);

// squeak with frequency in Hz
VOID beep (Uint16_T Freq);

// squeak with a frequency in Hz Amount times, active High time, Low silence
VOID BEEP (UINT16_T FREQ, UINT16_T AMOUNT, UINT16_T HIGH, UINT16_T LOW = 0);

// squeak with a note (prefix note_)
VOID beepnote (Uint8_t Note);

// squeak with a note of amount times, active time high, silence of Low
VOID BEEPNOTE (UINT8_T NOTE, UINT16_T AMOUNT, UINT16_T HIGH, UINT16_T LOW = 0);

Bool Tick ();// ticker, call in LOOP.Will return it if the squeak is actively
VOID Stop ();// Stop work
Void Usetone (Bool F);// Use the implementation of Tone instead of a manual timer (silence. FALSE)

// inherits from Blinker:
VOID Init (Uint8_T PIN);// Indicate the pin
VOID Invert (Bool Inv);// Invert the output
VOID form ();// provoke a call reign
Bool Ready ();// will return True once when the piking of the lawCranberries are silent
Bool Running ();// returns True while the system picks up
Bool state ();// Exit status (there is a squeak generation)
uint16_t getleft ();// get the rest until the next switch to ms
uint8_t getleft8 ();// get the rest until the next switch in the range 0-255
`` `

<a id="EXAMPLE"> </a>

## Example
### just pour
`` `CPP
#include <beeper.h>
Beeper Buz (13);

VOID setup () {
  // PICK NOTE NOTE_G1 3 times, 500MS VKL, 300MS off
  buz.beepnote (Note_g1, 3, 500, 300);
}
VOID loop () {
  buz.tick ();
}
`` `

### play three notes
`` `CPP
#include <beeper.h>
Beeper Buz (13);
uint8_t notes [] = {note_ass, note_ass, note_f3};
uint8_t curnote = 0;

VOID Start () {
  curnote = 0;
  Buz.Force ();// provoke Ready
}

VOID setup () {
  Start ();
}
VOID loop () {
  buz.tick ();

  // Switch the note
  if (buz.ready ()) {
    if (curnote <3) {
      buz.beepnote (notes [curnote], 1, 500, 500);
      Curnote ++;
    }
  }
}
`` `

<a id="versions"> </a>
## versions
- V1.0

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!

When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code