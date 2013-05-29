#!/bin/awk -f

function TrimId() {
i = $1
sub(/[^[:blank:]]+[[:blank:]]+/, "")
}


BEGIN {
if (ARGC == 1) {
	print "Usage: " ARGV[0] " <msgid-file> [<msgstr-file>]"
	exit
} else {
	idfile = ARGV[1]
	while (getline <idfile) {
		TrimId()
		msgid[i] = $0
	}
	delete ARGV[1]
}
}


{
TrimId()
if (length(msgid[i]) != 0) {
	a = substr($0, 1, 2)
	b = substr(msgid[i], 1, 2)
	if (a == "\\n" && b != "\\n")
		sub(/^(\\n)+/, "")
	else if (b == "\\n" && a != "\\n")
		$0 = "\\n" $0
	a = substr($0, length() - 1)
	b = substr(msgid[i], length(msgid[i]) - 1)
	if (a == "\\n" && b != "\\n")
		sub(/(\\n)+$/, "")
	else if (b == "\\n" && a != "\\n")
		$0 = $0 "\\n"
	msgstr[i] = $0
}
}


END {
print "msgid \"\""
print "msgstr \"\""
print "\"Project-Id-Version: kshutdown\\n\""
print "\"MIME-Version: 1.0\\n\""
print "\"Content-Type: text/plain; charset=UTF-8\\n\""
print "\"Content-Transfer-Encoding: 8bit\\n\""
for (i in msgid) {
	if (msgid[i]!~/^$|^MSGTR_/) {
		print "# " i "\n" "msgid " "\"" msgid[i] "\"\n" "msgstr " "\"" msgstr[i] "\"\n"
		if (msgstr[i]~/^$/)
			print "mp_msg2po: " i " don't translated" > "/dev/stderr"
	}
}
}
