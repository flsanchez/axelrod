#!bin/bash
for i in {1..10}
do
	../bin/axelrod.e
	python imgAxelrod.py
	ffmpeg -f image2 -i %d.png -vcodec libx264 -crf 25 -s 1920x1080 video$i.mp4
	rm *.png
	rm *.txt
done
cd result/
ffmpeg -framerate 24 -i joinres%d.png final.mp4