#!bin/bash

../bin/axelrod.e
python imgAxelrod.py
ffmpeg -f image2 -i %d.png -vcodec libx264 -crf 25 -s 1920x1080 video.mp4