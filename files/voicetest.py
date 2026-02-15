import os
from dotenv import load_dotenv
from elevenlabs.client import ElevenLabs

load_dotenv()
client = ElevenLabs(api_key=os.getenv("ELEVEN_API_KEY"))

# 1. Generate the audio
audio = client.text_to_speech.convert(
    text="Glove system online. Ready to measure force.",
    voice_id="JBFqnCBsd6RMkjVDRZzb", 
    model_id="eleven_multilingual_v2"
)

# 2. Save it to a file (This works on all Python versions)
with open("speech.mp3", "wb") as f:
    for chunk in audio:
        f.write(chunk)

# 3. Play it using Windows' built-in command
os.system("start /min speech.mp3")