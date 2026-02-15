# MakeUofT2026

MakeUofT2026 Project: No One Bites The Dust (Wearable CPR Guide)

Winner (Category)

# Inspiration

Current CPR training relies heavily on vague instructions and limited-access mannequins. Trainees often practice on layered plastic with minimal feedback, making it difficult to objectively evaluate compression rate and force.

No One Bites The Dust replaces mannequin guesswork with real-time, data-driven feedback in a wearable form.

# What It Does

A wearable CPR guide worn on the non-dominant hand that measures:

✅ Compression rate (target: 120 BPM)

✅ Compression force (via force sensor)

✅ Real-time feedback (audio + visual cues)

✅ Force-time graph visualization with Python

# Features

🎵 Plays music at 120 BPM to guide compression rate

🔵 Blue LED flashes in sync with ideal rhythm

📊 Displays compression force over time

🔴 Red LED warns for excessive or insufficient force

Training becomes measurable, repeatable, and accessible — without a mannequin.


# Hardware:

Glove-mounted force sensor

Arduino-based microcontroller

Breadboard circuitry

3D-printed arm band

LEDs + audio output module


# Arduino Software:

C++ (PlatformIO)

Force sensor data collection

LED + audio control


# Python Software:

Compression-per-minute calculation

Maximum force analysis

Force-time graph generation

The system streams sensor data via Serial to Python for processing and visualization.

# Challenges
Cross-language Data Mismatch
Arduino (C++) → Serial → Python
Raw data noise (delays, zero values) caused inaccurate readings


# Built With

Arduino

C++

PlatformIO

Python

ElevenLabs

Gemini API

# Devpost Link:
https://devpost.com/software/no-one-bites-the-dust?ref_content=my-projects-tab&ref_feature=my_projects
