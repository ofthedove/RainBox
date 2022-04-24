# Rain Box
I noticed that it's much easier to put James down for a nap or for bed if there's some white noise or rain noise playing. The noise covers any little creaks or rustles of me leaving the room. For a trip to Marion/Calhoun it would be nice to have rain noise all the time, since it tends to be noisy and busy which gives him trouble sleeping. While we could use a phone or laptop with Spotify, I don't really want to lose access to whatever device we use. Also, rain noise on Spotify is annoyingly always podcasts, which means they end and I don't think they loop. Also, it might auto play something else, it might crash, etc. So a dedicated, stand-alone device would be ideal.

## First Iteration
The first iteration used my Teensy 4.0 and Audio board since I've used it for a noise-making project before. I know it has lots of powerful and easy to use software in Arduino IDE, and it can give a headphone output with no soldering/breadboarding/etc.

I started with an old bluetooth speaker with aux in, but it has a physical power switch and the battery only lasts a couple hours. To upgrade I got a power strip with USB charger and a set of USB powered speakers so everything is controlled by the switch on the power strip. Just flip it on and it starts raining.

I made a case to protect it rattling around in my backpack and on random tables and floors, in [Enclosure](Enclosure).

I made a loop-able rain noise sample in [Audio](Audio). It's one minute long and will play on loop forever. The fact that it loops isn't very noticable, since it's just noise anyway.

I made two Arduino sketches in [Software](Software). The first one plays a few different kinds of noise. We were only using rain though, which annoyingly wasn't the default. So I made a new sketch that only plays rain noise. I would have edited the original but I didn't have access to it because it was on my desktop at home.

### Useful Links
[Teensy 4.0](https://www.pjrc.com/store/teensy40.html)

[Teesny Audio Board](https://www.pjrc.com/store/teensy3_audio.html)

[Audio Design Tool](https://www.pjrc.com/teensy/gui/index.html) contains the documentation for the various audio library objects.

The built-in examples in the Arduino IDE (after installing Teensy extension) are useful. `Wav File Player USB` was useful for this project, but annoyingly didn't work as-is for the audio board. You need an `AudioControlSGTL5000` object and you need to call `enable` and `volume(0.5)` on it before you'll get any output. Also, the pin defines for the SD card are for the Teensy 3 version of the audio board, not the Teensy 4.
