#define SPEAKER_PIN 11
#define LED_PIN 13
#define TONE_FREQ_HZ 1000
#define BEEP_INTERVAL_AND_LENGTH_MILLIS 500

#define LED_MIRROR_SPEAKER

bool speaker_enabled;
bool speaker_on;
long last_speaker_change_millis = 0;

void setup_beep()
{
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
  
  #ifdef LED_MIRROR_SPEAKER
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, LOW);
  #endif
  
  speaker_enabled = false;
  speaker_on = false;
}

void enable_beep()
{
  speaker_enabled = true;
}

void disable_beep()
{
  speaker_enabled = false;
}

void start_beep()
{
  tone(SPEAKER_PIN, TONE_FREQ_HZ);
  
  #ifdef LED_MIRROR_SPEAKER
    digitalWrite(LED_PIN, HIGH);
  #endif
  
  speaker_on = true;
}

void end_beep()
{
  noTone(SPEAKER_PIN);
  
  #ifdef LED_MIRROR_SPEAKER
    digitalWrite(LED_PIN, LOW);
  #endif
  
  speaker_on = false;
}

void update_speaker()
{
  if(speaker_on)
    end_beep();
  else
    start_beep();
  last_speaker_change_millis = current_millis;
}
