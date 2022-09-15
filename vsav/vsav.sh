#/bin/bash

# A Fun little AV program by Stian Kvålshagen :]
# VSAV = Very sluggish anti virus

# Example: bash antivirus.sh the_rule_file.yar /home/user/
# How it works: bash antivirus.sh [the rule file] [the directory]
# Note that it will scan all files in sub directories.

# Colours & arrays

	GREEN="\e[32m"
	RED="\e[31m"
	BLUE="\e[34m"
	ENDCOLOR="\e[0m"
	fixed=()
	not_fixed=()

# Init prompt
	start_time=$(date +%s)
	echo "Welcome to VSAV! Scanning your directories based on your yara rules.."
	paths=$(yara $1 -r $2 2>/dev/null)
	end_time=$(date +%s)
	echo -e "${BLUE}Success!${ENDCOLOR}\n"
	elapsed=$(( end_time - start_time ))
	eval "echo Time to scan $2 : $(date -ud "@$elapsed" +'$((%s/3600/24)) days %H hr %M min %S sec')"
# Stop program if no virus if found

if [ -z "$paths" ];then
	echo -e "${GREEN}No virus found!${ENDCOLOR}"
else

# Split up the result

	readarray -t all_paths <<<"$paths"
	found=false
	echo -e "Number of items found: ${#all_paths[@]}"

for (( n=0; n < ${#all_paths[*]}; n++))
do

# Remove the hash warning

	found=true
	path="${all_paths[n]}"
for i in {1..5}
do
	path="${path:1}"
done

# Promt the user to delete the virus.

	echo -e "We found a very dangerous virus at: '$path'\nDo you want to remove it?[y/n]?"
	read choice
if [ "$choice" = "y" ]; then
	echo "Deleting $path"
	rm $path
	echo -e "${GREEN}File deleted!${ENDCOLOR}\n"
	fixed+="$path"
	sleep 1
fi
if [ "$choice" = "n" ]; then
	echo -e "${RED}Skipping malicious file..${ENDCOLOR}\n"
	not_fixed+="$path\n"
	sleep 1
fi
done
# Summary

	echo -e "${BLUE}Summary:${ENDCOLOR}\n"
if [ -z $fixed ];then
	echo -e "No virus fixed.\n"
else
	echo -e "${GREEN}Virus fixed:${ENDCOLOR}\n"
for (( n=0; n < ${#fixed[*]}; n++))
do
	echo -e "$fixed\n"
done
fi
if [ -z $not_fixed ];then
	echo -e "No virus skipped.\n"
else
	echo -e "${RED}Virus skipped:${ENDCOLOR}\n"
for (( n=0; n < ${#not_fixed[*]}; n++))
do
        echo -e "$not_fixed\n"
done
fi
fi
