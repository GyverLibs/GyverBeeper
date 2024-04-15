#pragma once

#include <Arduino.h>
#include <Blinker.h>
#include <limits.h>

#include "pitches.h"

#define BEEP_FOREVER INT8_MAX

class Beeper : public Blinker {
   public:
    // using Blinker::init;
    // using Blinker::force;
    // using Blinker::invert;
    // using Blinker::running;
    // using Blinker::ready;
    // using Blinker::state;
    // using Blinker::getLeft;
    // using Blinker::getLeft8;

    Beeper() {}

    // указать пин
    Beeper(uint8_t pin) {
        init(pin);
    }

    // использовать реализацию tone вместо ручного таймера
    void useTone(bool f) {
        _tone = f;
    }

    // true - синхронный режим (блокирующее пищание) для не-tone
    void syncMode(bool f) {
        _sync = f;
    }

    // остановить работу
    void stop() {
        Blinker::stop();
        if (_tone) noTone(Blinker::_pin);
    }

    // пищать с указанным периодом (мкс, или нота с префиксом US_)
    void beepUs(uint16_t us, bool force = true) {
        _tmr = micros();
        stop();
        _prd = _tone ? (1000000ul / us) : (us / 2);
        if (force) {
            if (_tone) tone(Blinker::_pin, _prd);
            else Blinker::_state = 1;
        }
    }

    // пискнуть с периодом us (мкс, или нота с префиксом US_) amount раз, активное время high, тишина low
    void beepUs(uint16_t us, int amount, uint16_t high, uint16_t low = 0) {
        beepUs(us, false);
        blink(amount, high, low);
    }

    // пискнуть с периодом us (мкс, или нота с префиксом US_), активное время high, тишина low
    void beepUsForever(uint16_t us, uint16_t high, uint16_t low = 0) {
        beepUs(us, INT8_MAX, high, low);
    }

    // пищать с частотой в Гц
    void beep(uint16_t freq) {
        beepUs(1000000ul / freq);
    }

    // пискнуть с частотой в Гц amount раз, активное время high, тишина low
    void beep(uint16_t freq, int amount, uint16_t high, uint16_t low = 0) {
        beepUs(1000000ul / freq, amount, high, low);
    }

    // пискнуть с частотой в Гц, активное время high, тишина low
    void beepForever(uint16_t freq, int amount, uint16_t high, uint16_t low = 0) {
        beep(freq, INT8_MAX, high, low);
    }

    // пищать с нотой (префикс NOTE_)
    void beepNote(uint8_t note) {
        beepUs(pgm_read_word(&gbeeper::notes[note]));
    }

    // пискнуть нотой amount раз, активное время high, тишина low
    void beepNote(uint8_t note, int amount, uint16_t high, uint16_t low = 0) {
        beepUs(pgm_read_word(&gbeeper::notes[note]), amount, high, low);
    }

    // пискнуть нотой, активное время high, тишина low
    void beepNoteForever(uint8_t note, uint16_t high, uint16_t low = 0) {
        beepNote(note, INT8_MAX, high, low);
    }

    // тикер, вызывать в loop. Вернёт true, если пищание активно
    bool tick() {
        do {
            if (Blinker::tick()) {
                if (state()) {
                    _tmr = micros();
                    _state = 1;
                    if (_tone) tone(Blinker::_pin, _prd);
                } else {
                    if (_tone) noTone(Blinker::_pin);
                    else _write(0);
                }
            }

            if (!_tone && state() && (uint16_t)((uint16_t)micros() - _tmr) >= _prd) {
                _tmr += _prd;
                _write(_state = !_state);
            }
        } while (_sync && !_tone && state());

        return state();
    }

   private:
    using Blinker::_write;
    using Blinker::blink;
    using Blinker::stop;
    using Blinker::tick;

    uint16_t _tmr = 0, _prd = 0;
    bool _state = 0;
    bool _tone = 0;
    bool _sync = 0;
};