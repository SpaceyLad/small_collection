echo -e "Hello there! Please choose which story you want to scan :]\n1. Main story\n2. A Study In Scarlet \n3. The Sign of the Four \n4. The Hound of the Baskervilles \n5. The Valley of Fear"

read choice
echo "Downloading choice nr.$choice"

if [ "$choice" = "1" ]; then
curl -s https://sherlock-holm.es/stories/plain-text/cano.txt > story.txt
fi
if [ "$choice" = "2" ]; then
curl -s https://sherlock-holm.es/stories/plain-text/stud.txt > story.txt
fi
if [ "$choice" = "3" ]; then
curl -s https://sherlock-holm.es/stories/plain-text/sign.txt > story.txt
fi
if [ "$choice" = "4" ]; then
curl -s https://sherlock-holm.es/stories/plain-text/houn.txt > story.txt
fi
if [ "$choice" = "5" ]; then
curl -s https://sherlock-holm.es/stories/plain-text/vall.txt > story.txt
fi
echo "Download successfull! Stored in story.txt"

echo "What word are you looking for?"
read word

number=$(cat story.txt | grep "$word"|wc -l)

echo "The story has '$word' mentioned in $number lines!"
sleep 2
echo "Deleting story.txt"
rm story.txt
