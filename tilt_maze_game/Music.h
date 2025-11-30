#ifndef MUSIC_H
#define MUSIC_H

#include <Arduino.h>

const int speakerPin = A0;
extern unsigned long lastNoteTime;
extern int currentNote;
extern int currentTrack;
extern bool musicEnabled;

#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_REST 0

// Menu music - Chill funky groove
const int menuMelody[] = {
  NOTE_E3, NOTE_REST, NOTE_E3, NOTE_G3, NOTE_REST, NOTE_A3, NOTE_REST, NOTE_G3,
  NOTE_REST, NOTE_E3, NOTE_REST, NOTE_D3, NOTE_E3, NOTE_REST, NOTE_REST, NOTE_G3,
  NOTE_A3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_G3, NOTE_A3,
  NOTE_REST, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_REST,
  NOTE_D3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_A3, NOTE_REST,
  NOTE_G3, NOTE_E3, NOTE_REST, NOTE_D3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_REST
};
const int menuDurations[] = {
  120, 60, 120, 120, 60, 180, 60, 120,
  60, 120, 60, 120, 180, 60, 60, 120,
  180, 60, 120, 60, 120, 60, 120, 180,
  60, 120, 120, 180, 60, 120, 60, 60,
  120, 60, 180, 60, 120, 60, 180, 60,
  120, 120, 60, 120, 60, 180, 60, 60
};
const int menuLength = 48;

// Level 1 - Laid back funky bass
const int level1Melody[] = {
  NOTE_E3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_A3, NOTE_AS3,
  NOTE_A3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_D3, NOTE_REST,
  NOTE_E3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_A3, NOTE_REST, NOTE_C4, NOTE_REST,
  NOTE_AS3, NOTE_A3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_E3, NOTE_REST, NOTE_REST,
  NOTE_D3, NOTE_REST, NOTE_D3, NOTE_E3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_A3,
  NOTE_REST, NOTE_AS3, NOTE_A3, NOTE_REST, NOTE_G3, NOTE_E3, NOTE_REST, NOTE_REST
};
const int level1Durations[] = {
  140, 60, 140, 60, 140, 60, 100, 100,
  140, 60, 140, 60, 140, 60, 140, 60,
  140, 60, 140, 60, 140, 60, 200, 60,
  100, 140, 60, 140, 60, 200, 60, 60,
  140, 60, 100, 140, 60, 140, 60, 200,
  60, 100, 140, 60, 140, 200, 60, 60
};
const int level1Length = 48;

// Level 2 - Upbeat groovy
const int level2Melody[] = {
  NOTE_A3, NOTE_REST, NOTE_C4, NOTE_REST, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST,
  NOTE_D4, NOTE_C4, NOTE_REST, NOTE_A3, NOTE_REST, NOTE_G3, NOTE_REST, NOTE_REST,
  NOTE_A3, NOTE_REST, NOTE_A3, NOTE_C4, NOTE_REST, NOTE_D4, NOTE_E4, NOTE_REST,
  NOTE_G4, NOTE_REST, NOTE_E4, NOTE_D4, NOTE_REST, NOTE_C4, NOTE_REST, NOTE_REST,
  NOTE_D4, NOTE_REST, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST, NOTE_D4, NOTE_C4,
  NOTE_REST, NOTE_A3, NOTE_REST, NOTE_G3, NOTE_A3, NOTE_REST, NOTE_REST, NOTE_REST
};
const int level2Durations[] = {
  120, 40, 120, 40, 120, 40, 160, 40,
  100, 120, 40, 120, 40, 160, 40, 40,
  120, 40, 100, 120, 40, 120, 160, 40,
  200, 40, 100, 120, 40, 160, 40, 40,
  120, 40, 100, 40, 120, 40, 100, 120,
  40, 120, 40, 100, 160, 40, 40, 40
};
const int level2Length = 48;

// Level 3 - Funky swagger
const int level3Melody[] = {
  NOTE_E4, NOTE_REST, NOTE_DS4, NOTE_E4, NOTE_REST, NOTE_G4, NOTE_REST, NOTE_A4,
  NOTE_REST, NOTE_G4, NOTE_E4, NOTE_REST, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST,
  NOTE_REST, NOTE_A3, NOTE_REST, NOTE_C4, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST,
  NOTE_G4, NOTE_REST, NOTE_A4, NOTE_G4, NOTE_REST, NOTE_E4, NOTE_REST, NOTE_REST,
  NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST, NOTE_G4, NOTE_A4, NOTE_REST, NOTE_G4,
  NOTE_REST, NOTE_E4, NOTE_D4, NOTE_REST, NOTE_E4, NOTE_REST, NOTE_REST, NOTE_REST
};
const int level3Durations[] = {
  100, 30, 80, 100, 30, 100, 30, 140,
  30, 100, 100, 30, 100, 30, 140, 30,
  30, 100, 30, 100, 100, 30, 140, 30,
  140, 30, 100, 100, 30, 140, 30, 30,
  100, 30, 100, 30, 100, 140, 30, 100,
  30, 100, 100, 30, 180, 30, 30, 30
};
const int level3Length = 48;

// Level 4 - Intense groove
const int level4Melody[] = {
  NOTE_A4, NOTE_REST, NOTE_A4, NOTE_G4, NOTE_REST, NOTE_A4, NOTE_REST, NOTE_C5,
  NOTE_REST, NOTE_AS4, NOTE_A4, NOTE_REST, NOTE_G4, NOTE_REST, NOTE_E4, NOTE_REST,
  NOTE_D4, NOTE_REST, NOTE_E4, NOTE_G4, NOTE_REST, NOTE_A4, NOTE_REST, NOTE_C5,
  NOTE_REST, NOTE_AS4, NOTE_REST, NOTE_A4, NOTE_G4, NOTE_REST, NOTE_REST, NOTE_REST,
  NOTE_E4, NOTE_REST, NOTE_G4, NOTE_REST, NOTE_A4, NOTE_REST, NOTE_AS4, NOTE_A4,
  NOTE_REST, NOTE_G4, NOTE_REST, NOTE_E4, NOTE_REST, NOTE_D4, NOTE_E4, NOTE_REST
};
const int level4Durations[] = {
  80, 20, 80, 80, 20, 80, 20, 120,
  20, 80, 80, 20, 80, 20, 120, 20,
  80, 20, 80, 80, 20, 80, 20, 120,
  20, 80, 20, 80, 80, 20, 20, 20,
  80, 20, 80, 20, 80, 20, 80, 80,
  20, 80, 20, 80, 20, 80, 120, 20
};
const int level4Length = 48;

// Level 5 - High energy finale
const int level5Melody[] = {
  NOTE_E5, NOTE_REST, NOTE_D5, NOTE_E5, NOTE_REST, NOTE_G5, NOTE_REST, NOTE_A5,
  NOTE_REST, NOTE_G5, NOTE_E5, NOTE_REST, NOTE_D5, NOTE_REST, NOTE_E5, NOTE_REST,
  NOTE_A4, NOTE_REST, NOTE_C5, NOTE_D5, NOTE_REST, NOTE_E5, NOTE_REST, NOTE_G5,
  NOTE_REST, NOTE_FS5, NOTE_G5, NOTE_REST, NOTE_E5, NOTE_D5, NOTE_REST, NOTE_REST,
  NOTE_E5, NOTE_REST, NOTE_E5, NOTE_D5, NOTE_REST, NOTE_E5, NOTE_G5, NOTE_REST,
  NOTE_A5, NOTE_REST, NOTE_G5, NOTE_E5, NOTE_REST, NOTE_D5, NOTE_E5, NOTE_REST
};
const int level5Durations[] = {
  70, 20, 70, 70, 20, 70, 20, 100,
  20, 70, 70, 20, 70, 20, 100, 20,
  70, 20, 70, 70, 20, 70, 20, 100,
  20, 70, 100, 20, 70, 70, 20, 20,
  70, 20, 70, 70, 20, 70, 100, 20,
  100, 20, 70, 70, 20, 70, 100, 20
};
const int level5Length = 48;

void updateMusic() {
  if (!musicEnabled) return;
  
  const int* melody;
  const int* durations;
  int length;
  
  if (currentTrack == 0) {
    melody = menuMelody;
    durations = menuDurations;
    length = menuLength;
  } else if (currentTrack == 1) {
    melody = level1Melody;
    durations = level1Durations;
    length = level1Length;
  } else if (currentTrack == 2) {
    melody = level2Melody;
    durations = level2Durations;
    length = level2Length;
  } else if (currentTrack == 3) {
    melody = level3Melody;
    durations = level3Durations;
    length = level3Length;
  } else if (currentTrack == 4) {
    melody = level4Melody;
    durations = level4Durations;
    length = level4Length;
  } else {
    melody = level5Melody;
    durations = level5Durations;
    length = level5Length;
  }
  
  if (millis() - lastNoteTime >= durations[currentNote]) {
    noTone(speakerPin);
    currentNote = (currentNote + 1) % length;
    lastNoteTime = millis();
    
    if (melody[currentNote] > 0) {
      tone(speakerPin, melody[currentNote], durations[currentNote] - 10);
    }
  }
}

void switchTrack(int track) {
  currentTrack = track;
  currentNote = 0;
  lastNoteTime = millis();
}

void stopMusic() {
  noTone(speakerPin);
}

#endif