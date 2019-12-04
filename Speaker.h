#define SPEAKER_PIN 11
#define TONE_FREQ_HZ 1000
#define BEEP_INTERVAL_AND_LENGTH_MILLIS 500

bool speaker_enabled;
bool speaker_on;
long last_speaker_change_millis = 0;

void setup_beep()
{
  pinMode(SPEAKER_PIN, OUTPUT);
  digitalWrite(SPEAKER_PIN, LOW);
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
  last_speaker_change_millis = millis();
  tone(SPEAKER_PIN, TONE_FREQ_HZ);
  speaker_on = true;
}

void end_beep()
{
  last_speaker_change_millis = millis();
  noTone(SPEAKER_PIN);
  speaker_on = false;
}

void update_speaker()
{
  if(speaker_on)
    end_beep();
  else
    start_beep();
}

