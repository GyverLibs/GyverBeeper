#include <Beeper.h>
Beeper buz(13);

void setup() {
  // пикнуть нотой NOTE_G1 3 раза, 500мс вкл, 300мс выкл
  buz.beepNote(NOTE_G1, 3, 500, 300);
}
void loop() {
  buz.tick();
}