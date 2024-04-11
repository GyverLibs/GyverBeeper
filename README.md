[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverBeeper.svg?color=brightgreen)](https://github.com/GyverLibs/GyverBeeper/releases/latest/download/GyverBeeper.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverBeeper.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverBeeper)
[![arduino-library](https://www.ardu-badge.com/badge/GyverBeeper.svg?)](https://www.ardu-badge.com/GyverBeeper)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverBeeper?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverBeeper
Генерация писка по таймеру
- Простыми словами: библиотека позволяет асинхронно пикнуть зуммером несколько раз
- Асинхронная работа
- Программный асинхронный писк на базе micros() или tone() по выбору
- Установка активного и пассивного времени
- Встроенная PGM таблица на 90 нот (от До контроктавы до Ми пятой октавы)

### Совместимость
Все Arduino

## Содержание
- [Установка](#install)
- [Использование](#usage)
- [Пример](#example)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Для работы требуется библиотека [GyverBlinker](https://github.com/GyverLibs/GyverBlinker)
- Библиотеку можно найти по названию **GyverBeeper** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverBeeper/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!

<a id="usage"></a>

## Использование
```cpp
// конструктор
Blinker();
Blinker(uint8_t pin);

// методы
// пищать с указанным периодом (мкс, или нота с префиксом US_)
void beepUs(uint16_t us);

// пискнуть с периодом us (мкс, или нота с префиксом US_) amount раз, активное время high, тишина low
void beepUs(uint16_t us, uint16_t amount, uint16_t high, uint16_t low = 0);

// пищать с частотой в Гц
void beep(uint16_t freq);

// пискнуть с частотой в Гц amount раз, активное время high, тишина low
void beep(uint16_t freq, uint16_t amount, uint16_t high, uint16_t low = 0);

// пищать с нотой (префикс NOTE_)
void beepNote(uint8_t note);

// пискнуть нотой amount раз, активное время high, тишина low
void beepNote(uint8_t note, uint16_t amount, uint16_t high, uint16_t low = 0);

bool tick();            // тикер, вызывать в loop. Вернёт true если пищание активно
void stop();            // остановить работу
void useTone(bool f);   // использовать реализацию tone вместо ручного таймера (умолч. false)

// наследует из Blinker:
void init(uint8_t pin); // указать пин
void invert(bool inv);  // инвертировать выход
void force();           // спровоцировать вызов ready
bool ready();           // однократно вернёт true, когда пикание закончится
bool running();         // возвращает true, пока система пикает
bool state();           // статус выхода (идёт генерация писка)
uint16_t getLeft();     // получить остаток до следующего переключения в мс
uint8_t getLeft8();     // получить остаток до следующего переключения в диапазоне 0-255
```

<a id="example"></a>

## Пример
### Просто пикнуть
```cpp
#include <Beeper.h>
Beeper buz(13);

void setup() {
  // пикнуть нотой NOTE_G1 3 раза, 500мс вкл, 300мс выкл
  buz.beepNote(NOTE_G1, 3, 500, 300);
}
void loop() {
  buz.tick();
}
```

### Играть три ноты
```cpp
#include <Beeper.h>
Beeper buz(13);
uint8_t notes[] = {NOTE_ASS, NOTE_ASS, NOTE_F3};
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
```

<a id="versions"></a>
## Версии
- v1.0

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!

При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код