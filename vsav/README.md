# Very Sluggish Anti Virus

These 2 files will scan your Linux machine for a certain [or more] hashes.
Its a very simple script where you have to add hashes yourself.

## How to:
### Change hash
Edit the Yara file to the hash you want to search for.
### Delete the files
Make sure to run as root if ran outside home directory!

## Example syntax
bash vsav.sh hash.yar /home
bash [file] [rule] [directory]

## Screenshots
![image](https://user-images.githubusercontent.com/87969837/190512358-6d9455cc-326b-4117-988b-f25b2d2284d0.png)
