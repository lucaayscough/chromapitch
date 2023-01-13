Resources used:

YIN paper:
http://audition.ens.fr/adc/pdf/2002_JASA_YIN.pdf

C implmentation:
https://github.com/ashokfernandez/Yin-Pitch-Tracking

Frequency to midi conversion: 
https://newt.phys.unsw.edu.au/jw/notes.html


TODO:

Improve YIN and add probability measurement;
Implement BACF method and test to see which is better;
Pre-compute lookup tables for frequency conversions;
Fix issue where agorithm doesn't work at low buffer sizes (works at 128 but not at 64);
Filter signal and then down-sample for faster processing?;
Incorrect pitch readings on "E" vowel;
Frames update faster than YIN algorithm;
