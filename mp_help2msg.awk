#!/bin/gawk -f


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


function ProtectQuote() {
return gensub(/([^\\])"/, "\\1\\\\\"", "g")
}


BEGIN {
defs["HELP_MP_DEFINE_STATIC"]=1
while (getline <"../config.h") {
    Trim()
    if ($0~/^#define[[:blank:]]+/) defs[$2]=1
}
ifdef_level=0
IsHelp=0
IsDefine=0
}


{
Trim()
}


/^#endif/ {
ifdef_level=rshift(ifdef_level, 1)
next
}


/^#ifdef/ {
ifdef_level=lshift(ifdef_level, 1)
if (defs[$2]!=1) ifdef_level++
next
}


ifdef_level!=0 {
next
}


IsHelp!=0 {
ClearStr()
if ($0~/;$/) {
    IsHelp=0
    sub(/[[:blank:]]*;$/, "")
    sub(/"[[:blank:]]*$/, "")
}
msg["Help_text"]=msg["Help_text"] $0
}


IsDefine!=0 {
if ($0!~/\\$/) IsDefine=0
ClearStr()
msg[i]=msg[i] ProtectQuote()
}


/static[[:blank:]]+char[[:blank:]]+help_text/ {
sub(/^static[[:blank:]]+char[[:blank:]]+help_text.*=[[:blank:]]*/, "")
ClearStr()
msg["Help_text"]=$0
if ($0~/;$/) sub(/[[:blank:]]*;$/, "")
else IsHelp=1
}


/^#define[[:blank:]]+MSGTR_/ {
if ($0~/\\$/) IsDefine=1
i=$2
sub(/^#define[[:blank:]]+MSGTR_[^[:blank:]]+[[:blank:]]+/, "")
if ($0~/\\$/) IsDefine=1
ClearStr()
msg[i]=msg[i] ProtectQuote()
}


function OutStr() {
return i " " msg[i]
}


END {
for (i in msg) print OutStr() | "sort --key=2 | uniq --skip-fields=1 | sort"
}
