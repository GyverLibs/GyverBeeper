#include <Beeper.h>
Beeper buz(13);
uint8_t notes[] = {NOTE_F4, NOTE_AS1, NOTE_F3};
uint8_t curNote = 0;

void start() {
  curNote = 0;
  buz.force();  // спровоцировать ready
}

void setup() {
  start();
}
void loop() {
  buz.tick();

  // переключить ноту
  if (buz.ready()) {
    if (curNote < 3) {
      buz.beepNote(notes[curNote], 1, 500, 500);
      curNote++;
    }
  }
}