#pragma once

#include <Arduino.h>
#include <Blinker.h>

#include "pitches.h"

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
    void beepUs(uint16_t us, uint16_t amount, uint16_t high, uint16_t low = 0) {
        beepUs(us, false);
        blink(amount, high, low);
    }

    // пищать с частотой в Гц
    void beep(uint16_t freq) {
        beepUs(1000000ul / freq);
    }

    // пискнуть с частотой в Гц amount раз, активное время high, тишина low
    void beep(uint16_t freq, uint16_t amount, uint16_t high, uint16_t low = 0) {
        beepUs(1000000ul / freq, amount, high, low);
    }

    // пищать с нотой (префикс NOTE_)
    void beepNote(uint8_t note) {
        beepUs(pgm_read_word(&_notes[note]));
    }

    // пискнуть нотой amount раз, активное время high, тишина low
    void beepNote(uint8_t note, uint16_t amount, uint16_t high, uint16_t low = 0) {
        beepUs(pgm_read_word(&_notes[note]), amount, high, low);
    }

    // тикер, вызывать в loop. Вернёт true если пищание активно
    bool tick() {
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

        return state();
    }

   private:
    using Blinker::_write;
    using Blinker::blink;
    using Blinker::stop;
    using Blinker::tick;

    uint16_t _tmr, _prd;
    bool _state = 0;
    bool _tone = 0;
};