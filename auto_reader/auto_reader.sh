#!/bin/bash

sleep .5
echo "   _____          __          ____  __.       __           "
sleep .5
echo "  /  _  \  __ ___/  |_  ____ |    |/ _|____  |  | __ ____  "
sleep .5
echo " /  /_\  \|  |  \   __\/  _ \|      < \__  \ |  |/ // __ \ "
sleep .5
echo "/    |    \  |  /|  | (  <_> )    |  \ / __ \|    <\  ___/ "
sleep .5
echo "\____|__  /____/ |__|  \____/|____|__ (____  /__|_ \\___  >"
sleep .5
echo "        \/                           \/    \/     \/    \/ "

echo -e "\nDownloading $1"
curl -s $1 > file_with_content.txt
echo "Done!"

echo "Opening the downloaded file in 3 seconds.."
sleep 3
cat file_with_content.txt

echo "Deleting file in 3 seconds.."
sleep 3
rm file_with_content.txt

echo " "
echo "Done! Have a great day :]"
