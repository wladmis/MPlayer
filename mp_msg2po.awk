#!/bin/awk -f

function Trim() {
sub(/\/\*.*\*\//, "")
sub(/[[:blank:]]+\/\/.*$/, "")
sub(/^[[:blank:]]+/, "")
sub(/[[:blank:]]+$/, "")
sub(/^#[[:blank:]]+/, "#")
}

function ClearStr() {
sub(/[[:blank:]]*\\$/, "")
sub(/"[[:blank:]]*$/, "")
sub(/^[[:blank:]]*"/, "")
sub(/^\\\\n/, "\\n")
sub(/\\\\n$/, "\\n")
}


function ReadLine() {
return getline
Trim()
}


function Func1() {
i=$1
sub(/[^[:blank:]]+[[:blank:]]+/, "")
}


BEGIN {
if (ARGC==1) {
    print "Usage: " ARGV[0] " <msgid-file> [<msgstr-file>]"
    exit
} else {
    idfile=ARGV[1]
    while (getline <idfile) {
	Func1()
	msgid[i]=$0
    }
    delete ARGV[1]
}
}


{
Func1()
if (length(msgid[i])!=0) {
	if (substr($0, 1, 2)=="\\n" && substr(msgid[i], 1, 2)!="\\n") sub(/^(\\n)+/, "")
	else if (substr(msgid[i], 1, 2)=="\\n" && substr($0, 1, 2)!="\\n") $0="\\n" $0
	if (substr($0, length()-1)=="\\n" && substr(msgid[i], length(msgid[i])-1)!="\\n") sub(/(\\n)+$/, "")
	else if (substr(msgid[i], length(msgid[i])-1)=="\\n" && substr($0, length()-1)!="\\n") $0=$0 "\\n"
	if (msgid[i]!=$0) msgstr[i]=$0
    }
}


END {
for (i in msgid) if (length(msgid[i])!=0) print "# " i "\n" "msgid " "\"" msgid[i] "\"\n" "msgstr " "\"" msgstr[i] "\"\n"
}
